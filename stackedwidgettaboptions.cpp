#include "stackedwidgettaboptions.h"
#include "ui_stackedwidgettaboptions.h"

StackedWidgetTabOptions::StackedWidgetTabOptions(QWidget *parent):
    QStackedWidget(parent),
    ui(new Ui::StackedWidgetTabOptions)
{
    ui->setupUi(this);
}

StackedWidgetTabOptions::~StackedWidgetTabOptions()
{
    delete ui;
}
