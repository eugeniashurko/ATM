#include "withdrawresultok.h"
#include "ui_withdrawresultok.h"
#include "../dialogues/withdrawalreceipt.h"

WithdrawResultOk::WithdrawResultOk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WithdrawResultOk)
{
    ui->setupUi(this);
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
    WithdrawalReceipt * d = new WithdrawalReceipt;
    connect(d, SIGNAL(withdrawed()), this, SLOT(on_actionCompleted()));
    d->setSum(_sum);
    d->setWindowTitle("Withdrawal Receipt");
    d->setModal(true);
    d->show();
}

void WithdrawResultOk::on_actionCompleted() {
    emit withdrawalCompleted();
}
