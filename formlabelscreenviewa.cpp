#include "formlabelscreenviewa.h"
#include "ui_formlabelscreenviewa.h"

FormLabelScreenViewA::FormLabelScreenViewA(QWidget *parent):
    QWidget(parent),
    ui(new Ui::FormLabelScreenViewA),
    sizes(new QList<int>()),
    tabList(new QList<QWidget*>()),
    plusTab(nullptr),
    tabCounter(1)
{
    ui->setupUi(this);
    sizes->append(ui->splitter->width() * 0.6);
    sizes->append(ui->splitter->width() * 0.4);
    ui->splitter->setSizes(*sizes);
    ui->tabWidget->setTabText(0, QString("Tab %1").arg(tabCounter));
    tabList->append(ui->tabWidget->widget(0));
    plusTab = new QWidget();
    ui->tabWidget->addTab(plusTab, QIcon(":/mlPlus.png"), QString());

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int index){
        if (index == ui->tabWidget->count() - 1) {
            tabCounter++;
            QWidget *newTab = new QWidget();
            tabList->append(newTab);
            QString tabName = QString("Tab %1").arg(tabCounter);
            ui->tabWidget->insertTab(ui->tabWidget->count() - 1, newTab, tabName);
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 2);
        }
    });

    connect(ui->tabWidget->tabBar(), &QTabBar::tabBarDoubleClicked, this, [=](int index){
        if (index >= 0 && index < ui->tabWidget->count() - 1) { // + 탭 제외
            bool ok;
            QString newName = QInputDialog::getText(this, tr("Rename Tab"), tr("New tab name:"), QLineEdit::Normal, ui->tabWidget->tabText(index), &ok);
            if (ok && !newName.isEmpty()) ui->tabWidget->setTabText(index, newName);
        }
    });
}

FormLabelScreenViewA::~FormLabelScreenViewA()
{
    delete sizes;
    delete tabList;
    delete ui;
}

void FormLabelScreenViewA::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int totalWidth = ui->splitter->width();
    int listWidth  = totalWidth * 0.6;
    int tabWidth   = totalWidth * 0.4;

    QList<int> newSizes;
    newSizes << listWidth << tabWidth;
    ui->splitter->setSizes(newSizes);
}
