#include "balancewidget.h"
#include "ui_balancewidget.h"

BalanceWidget::BalanceWidget(const int available, const int hold, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BalanceWidget)
{
    ui->setupUi(this);
    connect(ui->quickWithdrawalButton, SIGNAL(clicked()), this, SLOT(on_withdrawButton_clicked()));
    QString av(QString::number(available));
    QString ov(QString::number(available+hold));
    ui->availableLabel->setText(av);
    ui->overallLabel->setText(ov);
}

BalanceWidget::~BalanceWidget()
{
    delete ui;
}

void BalanceWidget::on_withdrawButton_clicked() {
    emit fromBalanceWithdrawCalled();
}
