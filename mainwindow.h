#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QString>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QDateTime>
#include <QHostAddress>
#include <QMessageBox>
#include <QNetworkInterface>

#include "formlabelscreenviewa.h"
#include "formlabelscreenviewb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void handleIPInput(const QString &text);
    void moveFocusOnTab();
    void updateComboBoxHistory(QComboBox *combo, const QString &text, const QString &label, const QDateTime &timestamp);
    void updatePortHistory(const QString &port, const QString &label);
    void tryConnect();
    void refreshPresentIPs();

private:
    Ui::MainWindow *ui;
    FormLabelScreenViewA *sViewA;
    FormLabelScreenViewB *sViewB;
    QVBoxLayout *lA;
    QVBoxLayout *lB;

    QString savedIP;
    QString savedPort;

    QString validateAndNormalize(const QString &ip, const QString &type);
    QString formatWithTimestamp(const QString &value, const QString &label, const QDateTime &timestamp);
};
#endif // MAINWINDOW_H
