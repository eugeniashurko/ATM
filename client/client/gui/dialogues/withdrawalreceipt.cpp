#include "withdrawalreceipt.h"
#include "ui_withdrawalreceipt.h"

WithdrawalReceipt::WithdrawalReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WithdrawalReceipt)
{
    ui->setupUi(this);
}

WithdrawalReceipt::~WithdrawalReceipt()
{
    delete ui;
}
