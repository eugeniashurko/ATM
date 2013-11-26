#include "transferreceipt.h"
#include "ui_transferreceipt.h"

TransferReceipt::TransferReceipt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferReceipt)
{
    ui->setupUi(this);
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("ddd d MMMM  yy, hh:mm"));
}

TransferReceipt::~TransferReceipt()
{
    delete ui;
}

void TransferReceipt::on_farewellOkButton_clicked()
{
    this->close();
    emit periodicTransferComplete(this);
}



void TransferReceipt::setName(QString name) {
    ui->nameConfLabel->setText(name);
}

void TransferReceipt::setCard(QString card) {
    ui->accountConfLabel->setText(card);
}

void TransferReceipt::setSum(int sum) {
    ui->sumConfLabel->setText(QString::number(sum)+" UAH");
}

void TransferReceipt::setStartDate(QDate d) {
    ui->startDateConfLabel->setText(d.toString("dd.MM.yyyy"));
}

void TransferReceipt::setFrequency(Frequency f) {
    QString l="";
    switch(f) {
    case week:
        l = "Once in a week";
        break;
    case month:
        l = "Once in a month";
        break;
    case quarter:
        l = "Once in a quarter";
        break;
    case year:
        l = "Once in a year";
        break;
    default:
        break;
    }
    ui->freqConfLabel->setText(l);
}

void TransferReceipt::removeStartDate() {
    ui->startDateLabel->close();
    ui->startDateConfLabel->close();
}

void TransferReceipt::removeFrequency() {
    ui->freqConfLabel->close();
    ui->freqLabel->close();
}
