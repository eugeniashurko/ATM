#include "withdrawwidget.h"
#include "ui_withdrawwidget.h"
#include "periodic_tr_subwidgets/step3.h"


#include <QDebug>

WithdrawWidget::WithdrawWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WithdrawWidget)
{
    ui->setupUi(this);
}

WithdrawWidget::~WithdrawWidget()
{
    delete ui;
}

void WithdrawWidget::on_sum20Button_clicked()
{
    emit sum(20);
}

void WithdrawWidget::on_sum50Button_clicked()
{
    emit sum(50);
}

void WithdrawWidget::on_sum100Button_clicked()
{
    emit sum(100);
}

void WithdrawWidget::on_sum200Button_clicked()
{
     emit sum(200);
}

void WithdrawWidget::on_sum500Button_clicked()
{
     emit sum(500);
}


void WithdrawWidget::on_sumCustomButton_clicked()
{
    emit customSumInputCalled();
}
