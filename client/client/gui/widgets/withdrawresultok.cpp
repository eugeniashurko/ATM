#include "withdrawresultok.h"
#include "ui_withdrawresultok.h"

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
