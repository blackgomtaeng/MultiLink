#include "formlabelscreenviewb.h"
#include "ui_formlabelscreenviewb.h"

FormLabelScreenViewB::FormLabelScreenViewB(QWidget *parent):
    QWidget(parent),
    ui(new Ui::FormLabelScreenViewB)
{
    ui->setupUi(this);
    ui->comboBox->setItemIcon(0, QIcon(":/icons/mlCiclePlus.png"));
    ui->comboBox->setItemIcon(1, QIcon(":/icons/mlFiles.png"));
}

FormLabelScreenViewB::~FormLabelScreenViewB()
{
    delete ui;
}
