#include "formlabelscreenviewa.h"
#include "ui_formlabelscreenviewa.h"
#include "stackedwidgettaboptions.h"   // 여기서만 include

struct FormLabelScreenViewA::Impl {
    Ui::FormLabelScreenViewA* ui;
    TabStruct* tabs;
    BaseTypes bt;
    Impl(): ui(new Ui::FormLabelScreenViewA), tabs(new TabStruct) {}
    ~Impl() { delete tabs->plusIndex; delete tabs; delete ui; }
};

FormLabelScreenViewA::FormLabelScreenViewA(QWidget* parent)
    : QWidget(parent), d(new Impl)
{
    d->ui->setupUi(this);
    d->tabs->tabWidget = d->ui->tabWidget;
    d->tabs->tabWidget->clear();
    d->tabs->tabWidget->setTabsClosable(true);

    d->tabs->newTab = new QWidget;
    d->tabs->tabWidget->addTab(d->tabs->newTab, "New Tab");

    d->tabs->plusTab = new QWidget;
    d->tabs->tabWidget->addTab(d->tabs->plusTab, QIcon(":/mlPlus.png"), "");

    d->tabs->plusIndex = new int(d->tabs->tabWidget->count() - 1);
    d->tabs->tabWidget->tabBar()->setTabButton(*d->tabs->plusIndex, QTabBar::RightSide, nullptr);

    d->tabs->contextMenu = new QMenu(d->tabs->tabWidget);
    d->tabs->actionOptions = new QAction("Tab Options", d->tabs->contextMenu);
    d->tabs->actionClose = new QAction("Close Tab", d->tabs->contextMenu);
    d->tabs->contextMenu->addAction(d->tabs->actionOptions);
    d->tabs->contextMenu->addAction(d->tabs->actionClose);

    connect(d->tabs->tabWidget, &QTabWidget::tabBarClicked, this, &FormLabelScreenViewA::handleClickedTab);
    connect(d->tabs->tabWidget, &QTabWidget::tabCloseRequested, this, &FormLabelScreenViewA::handleTabCloseRequested);
    connect(d->tabs->tabWidget->tabBar(), &QTabBar::customContextMenuRequested, this, &FormLabelScreenViewA::showContextMenu);
    d->tabs->tabWidget->tabBar()->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(d->tabs->actionOptions, &QAction::triggered, this, &FormLabelScreenViewA::handleOptions);
    connect(d->tabs->actionClose, &QAction::triggered, this, &FormLabelScreenViewA::handleClose);
}

FormLabelScreenViewA::~FormLabelScreenViewA() { delete d; }

void FormLabelScreenViewA::handleClickedTab(int index) {
    if(index == d->tabs->tabWidget->count() - 1) {
        QWidget* newTab = new QWidget;
        d->tabs->tabWidget->insertTab(d->tabs->tabWidget->count() - 1, newTab, "New Tab");
        d->tabs->tabWidget->setCurrentIndex(d->tabs->tabWidget->count() - 2);
    }
}

void FormLabelScreenViewA::handleTabCloseRequested(int index) {
    if(index != d->tabs->tabWidget->count() - 1) {
        d->tabs->widget = d->tabs->tabWidget->widget(index);
        d->tabs->tabWidget->removeTab(index);
        delete d->tabs->widget;
    }
}

void FormLabelScreenViewA::showContextMenu(const QPoint& pos) {
    d->bt.index = d->tabs->tabWidget->tabBar()->tabAt(pos);
    if(d->bt.index >= 0 || d->bt.index == *d->tabs->plusIndex)
        d->tabs->contextMenu->exec(d->tabs->tabWidget->tabBar()->mapToGlobal(pos));
}

void FormLabelScreenViewA::handleOptions() {
    d->bt.count = d->tabs->tabWidget->count();
    d->bt.plusIdx = *d->tabs->plusIndex;
    d->bt.exists = false;
    for(int i = 0; i < d->bt.count; ++i) {
        if(d->tabs->tabWidget->tabText(i) == "Tab Options") {
            d->bt.exists = true;
            d->tabs->tabWidget->setCurrentIndex(i);
            break;
        }
    }
    if(!d->bt.exists) {
        auto* optionsWidget = new StackedWidgetTabOptions; // 반드시 QWidget 상속 필요
        d->tabs->tabWidget->insertTab(d->bt.plusIdx, optionsWidget, "Tab Options");
        d->tabs->tabWidget->setCurrentWidget(optionsWidget);
    }
}

void FormLabelScreenViewA::handleClose() {
    d->bt.index = d->tabs->tabWidget->currentIndex();
    if(d->bt.index != d->tabs->tabWidget->count() - 1) {
        d->tabs->widget = d->tabs->tabWidget->widget(d->bt.index);
        d->tabs->tabWidget->removeTab(d->bt.index);
        delete d->tabs->widget;
    }
}
