#include "overflowwidget.h"
#include "ui_overflowwidget.h"

OverflowWidget::OverflowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverflowWidget)
{
    ui->setupUi(this);
    setEmpty();
}

OverflowWidget::~OverflowWidget()
{
    delete ui;
}

void OverflowWidget::setEmpty() {
    ui->fullWidget->close();
    ui->emptyWidget->show();
    ui->cleanButton->setEnabled(false);
}

void OverflowWidget::setFilled(QString card, QString name, int max_sum) {
    if (!ui->cleanButton->isEnabled()) {
        ui->cleanButton->setEnabled(true);
    }
    ui->emptyWidget->close();
    ui->fullWidget->show();
    ui->maxSumLabel->setText(QString::number(max_sum) + " UAH");
    ui->cardLabel->setText(card);
    ui->nameLabel->setText(name);
}

void OverflowWidget::on_newSettingsButton_clicked()
{
    emit newOverflowCalled();
}

void OverflowWidget::on_cleanButton_clicked()
{
    emit cleanCalled();
}
