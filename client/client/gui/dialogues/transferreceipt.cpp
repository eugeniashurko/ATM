#include "transferreceipt.h"
#include "ui_transferreceipt.h"

TransferReceipt::TransferReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferReceipt)
{
    ui->setupUi(this);
}

TransferReceipt::~TransferReceipt()
{
    delete ui;
}

void TransferReceipt::on_farewellOkButton_clicked()
{
    this->close();
}
