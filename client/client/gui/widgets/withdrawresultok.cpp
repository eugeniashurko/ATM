#include "withdrawresultok.h"
#include "ui_withdrawresultok.h"
#include "../dialogues/withdrawalreceipt.h"

WithdrawResultOk::WithdrawResultOk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WithdrawResultOk)
{
    ui->setupUi(this);;
    ui->error1Widget->close();
    ui->error2Widget->close();
}

WithdrawResultOk::~WithdrawResultOk()
{
    delete ui;
}

void WithdrawResultOk::setSum(const int sum) {
    _sum = sum;
    ui->sumLabel->setText(QString::number(sum)+" UAH");
}

void WithdrawResultOk::on_backButton_clicked()
{
    emit backToSumInput();
}

void WithdrawResultOk::on_withdrawButton_clicked()
{
    // Here we check funds sufficiency
    bool suffFunds = true;
    int balance = 500;
    if ((balance - _sum) < 0) {
        suffFunds = false;
    }

    if (_sum <= 0) {
        showError(1);
    } else {
        if (!suffFunds) {
            showError(2);
        }
        else {
            WithdrawalReceipt * d = new WithdrawalReceipt;
            connect(d, SIGNAL(withdrawed()), this, SLOT(on_actionCompleted()));
            d->setSum(_sum);
            d->setWindowTitle("Withdrawal Receipt");
            d->setModal(true);
            d->show();
        }
    }

}

void WithdrawResultOk::on_actionCompleted() {
    emit withdrawalCompleted();
}

void WithdrawResultOk::showError(const int code) {
   if (code == 1) {
       ui->error1Widget->show();
   }
   else {
       ui->error2Widget->show();
   }
}
