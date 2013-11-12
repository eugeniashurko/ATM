#include <QDateTime>

#include "withdrawalreceipt.h"
#include "ui_withdrawalreceipt.h"

WithdrawalReceipt::WithdrawalReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WithdrawalReceipt)
{
    ui->setupUi(this);
    ui->dateLabel->setText(QDateTime::currentDateTime().toString(("ddd d MMMM  yy, hh:mm")));
}

WithdrawalReceipt::~WithdrawalReceipt()
{
    delete ui;
}

void WithdrawalReceipt::on_farewellOkButton_clicked()
{
    this->close();
    emit withdrawed();
}

void WithdrawalReceipt::setCard(const QString c) {
    ui->cardLabel->setText(c);
}

void WithdrawalReceipt::setSum(const int c) {
    ui->sumLabel->setText(QString::number(c) + "  UAH");
}
