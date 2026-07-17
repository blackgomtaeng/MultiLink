#include "formlabelscreenviewa.h"
#include "ui_formlabelscreenviewa.h"

FormLabelScreenViewA::FormLabelScreenViewA(QWidget *parent):
    QWidget(parent),
    ui(new Ui::FormLabelScreenViewA),
    tabs(new TabStruct)
{
    ui->setupUi(this);
    tabs->tabWidget = ui->tabWidget;

    tabs->tabWidget->clear();
    tabs->tabWidget->setTabsClosable(true);

    tabs->newTab = new QWidget;
    tabs->tabWidget->addTab(tabs->newTab, "New Tab");

    tabs->plusTab = new QWidget;
    tabs->tabWidget->addTab(tabs->plusTab, QIcon(":/mlPlus.png"), "");

    tabs->plusIndex = tabs->tabWidget->count() - 1;
    tabs->tabWidget->tabBar()->setTabButton(tabs->plusIndex, QTabBar::RightSide, nullptr);

    connect(tabs->tabWidget, &QTabWidget::tabBarClicked, this, &FormLabelScreenViewA::handleClickedTab);
    connect(tabs->tabWidget, &QTabWidget::tabCloseRequested, this, &FormLabelScreenViewA::handleTabCloseRequested);
}

FormLabelScreenViewA::~FormLabelScreenViewA() {
    delete tabs;
    delete ui;
}

void FormLabelScreenViewA::handleClickedTab(int index) {
    if (index == tabs->tabWidget->count() - 1) {
        QWidget *newTab = new QWidget;
        tabs->tabWidget->insertTab(tabs->tabWidget->count() - 1, newTab, "New Tab");
        tabs->tabWidget->setCurrentIndex(tabs->tabWidget->count() - 2);
    }
}

void FormLabelScreenViewA::handleTabCloseRequested(int index) {
    if (index != tabs->tabWidget->count() - 1) {
        tabs->widget = tabs->tabWidget->widget(index);
        tabs->tabWidget->removeTab(index);
        delete tabs->widget;
    }
}
