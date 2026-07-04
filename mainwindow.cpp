#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sViewA(new FormLabelScreenViewA(this)),
    sViewB(new FormLabelScreenViewB(this)),
    lA(new QVBoxLayout()),
    lB(new QVBoxLayout())
{
    ui->setupUi(this);
    ui->wScreen01->setLayout(lA);
    ui->wScreen02->setLayout(lB);
    lA->addWidget(sViewA);
    lB->addWidget(sViewB);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 0);

    ui->cb01PasswordCode->setEditable(true);
    ui->cb02IP->setEditable(true);
    ui->cb03PortNumber->setEditable(true);

    connect(ui->cb01PasswordCode->lineEdit(), &QLineEdit::editingFinished, this, [=](){ ui->cb02IP->setFocus(); });
    connect(ui->cb02IP->lineEdit(), &QLineEdit::editingFinished, this, [=](){ ui->cb03PortNumber->setFocus(); tryConnect(); });
    connect(ui->cb03PortNumber->lineEdit(), &QLineEdit::editingFinished, this, [=](){ tryConnect(); });

    refreshPresentIPs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::validateAndNormalize(const QString &ip, const QString &type) {
    QString trimmed = ip.trimmed();

    if (type == "IPv4") {
        QStringList parts = trimmed.split('.');
        if (parts.size() != 4) return "";
        for (int i = 0; i < parts.size(); ++i) {
            bool ok = false;
            int num = parts.at(i).toInt(&ok);
            if (!ok || num < 0 || num > 255) return "";
            parts[i] = QString::number(num);
        }
        return parts.join(".");
    }

    if (type == "IPv6") {
        QRegularExpression re(
            "^(?:[0-9A-Fa-f]{1,4}:){7}[0-9A-Fa-f]{1,4}$|"
            "^(?:[0-9A-Fa-f]{1,4}:){1,7}:$|"
            "^:(?:[0-9A-Fa-f]{1,4}:){1,7}$|"
            "^(?:[0-9A-Fa-f]{1,4}:){1,6}:[0-9A-Fa-f]{1,4}$"
            );
        if (!re.match(trimmed).hasMatch()) return "";
        QStringList parts = trimmed.split(':');
        for (int i = 0; i < parts.size(); ++i) parts[i] = parts.at(i).toLower();
        return parts.join(":");
    }

    return "";
}

QString MainWindow::formatWithTimestamp(const QString &value, const QString &label, const QDateTime &timestamp) {
    qint64 secs = timestamp.secsTo(QDateTime::currentDateTime());
    QString ago;
    if (secs < 60) ago = QString::number(secs) + "초 전";
    else if (secs < 3600) ago = QString::number(secs/60) + "분 전";
    else if (secs < 86400) ago = QString::number(secs/3600) + "시간 전";
    else if (secs < 2592000) ago = QString::number(secs/86400) + "일 전";
    else if (secs < 31104000) ago = QString::number(secs/2592000) + "달 전";
    else if (secs < 3110400000) ago = QString::number(secs/31104000) + "년 전";
    else ago = "세기 전";
    return value + " " + ago + " " + label;
}

void MainWindow::handleIPInput(const QString &text) {
    QString ipv4Result = validateAndNormalize(text, "IPv4");
    QString ipv6Result = validateAndNormalize(text, "IPv6");

    if (!ipv4Result.isEmpty()) {
        ui->cb02IP->setEditText(ipv4Result);
        savedIP = ipv4Result;
        updateComboBoxHistory(ui->cb02IP, ipv4Result, "", QDateTime::currentDateTime());
    } else if (!ipv6Result.isEmpty()) {
        ui->cb02IP->setEditText(ipv6Result);
        savedIP = ipv6Result;
        updateComboBoxHistory(ui->cb02IP, ipv6Result, "", QDateTime::currentDateTime());
    } else {
        ui->cb02IP->setEditText("");
        ui->cb02IP->setFocus();
    }
}

void MainWindow::moveFocusOnTab() {
    if (ui->cb01PasswordCode->hasFocus()) ui->cb02IP->setFocus();
    else if (ui->cb02IP->hasFocus()) ui->cb03PortNumber->setFocus();
}

void MainWindow::updateComboBoxHistory(QComboBox *combo, const QString &text, const QString &label, const QDateTime &timestamp) {
    for (int i = 0; i < combo->count(); ++i) {
        if (combo->itemData(i).toString() == text) {
            combo->removeItem(i);
            break;
        }
    }
    QString display = formatWithTimestamp(text, label, timestamp);
    //combo->insertItem(label.isEmpty() ? 1 : 0, display, text); // display는 힌트, userData는 실제 값
    //combo->setCurrentIndex(label.isEmpty() ? 1 : 0);
    combo->insertItem(combo->count(), display, text);
}

void MainWindow::updatePortHistory(const QString &port, const QString &label) {
    for (int i = 0; i < ui->cb03PortNumber->count(); ++i) {
        if (ui->cb03PortNumber->itemData(i).toString() == port) {
            ui->cb03PortNumber->removeItem(i);
            break;
        }
    }
    QString display = formatWithTimestamp(port, label, QDateTime::currentDateTime());
    //ui->cb03PortNumber->insertItem(label.isEmpty() ? 1 : 0, display, port);
    //ui->cb03PortNumber->setCurrentIndex(label.isEmpty() ? 1 : 0);
    ui->cb03PortNumber->insertItem(ui->cb03PortNumber->count(), display, port);
}

void MainWindow::tryConnect() {
    savedIP = ui->cb02IP->currentData().toString();
    savedPort = ui->cb03PortNumber->currentData().toString();

    if (!savedIP.isEmpty() && !savedPort.isEmpty()) {
        ui->statusbar->showMessage("Connecting to " + savedIP + ":" + savedPort);
        updatePortHistory(savedPort, "");
    }
}

void MainWindow::refreshPresentIPs() {
    QString presentIPv4, presentIPv6;

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
            presentIPv4 = address.toString();
        else if (address.protocol() == QAbstractSocket::IPv6Protocol && !address.isLoopback()) {
            presentIPv6 = address.toString();
            if (presentIPv6.contains('%'))
                presentIPv6 = presentIPv6.split('%').first();
        }
    }

    QString presentPort = "8080";
    QDateTime now = QDateTime::currentDateTime();

    auto addEntry = [&](const QString &ip, const QString &label) {
        if (!ip.isEmpty()) {
            updateComboBoxHistory(ui->cb02IP, ip, label, now);
            updatePortHistory(presentPort, label);
        }
    };

    addEntry(presentIPv4, "(P4)");
    addEntry(presentIPv6, "(P6)");
}
