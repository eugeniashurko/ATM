#include "balancewidget.h"
#include "ui_balancewidget.h"

BalanceWidget::BalanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BalanceWidget)
{
    ui->setupUi(this);
    connect(ui->quickWithdrawalButton, SIGNAL(clicked()), this, SLOT(on_withdrawButton_clicked()));
    // ! Here we get balance from db !
    int b = 10000;
    QString balance(QString::number(b));
    ui->sumOnBalanceLabel->setText(balance);

}

BalanceWidget::~BalanceWidget()
{
    delete ui;
}

void BalanceWidget::on_withdrawButton_clicked() {
    emit fromBalanceWithdrawCalled();
}
