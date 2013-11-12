#include "periodictransferreceipt.h"
#include "ui_periodictransferreceipt.h"

PeriodicTransferReceipt::PeriodicTransferReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PeriodicTransferReceipt)
{
    ui->setupUi(this);
}

PeriodicTransferReceipt::~PeriodicTransferReceipt()
{
    delete ui;
}
