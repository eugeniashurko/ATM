#include <QDateTime>

#include "withdrawalreceipt.h"
#include "ui_withdrawalreceipt.h"

WithdrawalReceipt::WithdrawalReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WithdrawalReceipt)
{
    ui->setupUi(this);
    ui->dateLabel->setText(QDateTime::currentDateTime().toString(("ddd d MMMM  yy, hh:mm")));
    setBankNotes(BanknoteCombination(0,0,0,0,0,0));
}

WithdrawalReceipt::~WithdrawalReceipt()
{
    delete ui;
}

void WithdrawalReceipt::on_farewellOkButton_clicked()
{
    this->close();
    emit withdrawed(this);
}

void WithdrawalReceipt::setCard(const QString c) {
    ui->cardLabel->setText(c);
}

void WithdrawalReceipt::setSum(const int c) {
    ui->sumLabel->setText(QString::number(c) + "  UAH");
}

void WithdrawalReceipt::setBankNotes(const BanknoteCombination& combo) {
    ui->note10->setText(QString::number(combo.get10()));
    ui->note20->setText(QString::number(combo.get20()));
    ui->note50->setText(QString::number(combo.get50()));
    ui->note100->setText(QString::number(combo.get100()));
    ui->note200->setText(QString::number(combo.get200()));
    ui->note500->setText(QString::number(combo.get500()));
}
