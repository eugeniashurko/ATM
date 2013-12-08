#include "withdrawresultok.h"
#include "ui_withdrawresultok.h"

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
    if (_sum > 0 )
        emit withdraw(_sum, this);
    else
        showError(1);
}

void WithdrawResultOk::showError(const int code) {
   if (code == 1) {
       ui->error1Widget->show();
   }
   else {
       ui->error2Widget->show();
   }
}
