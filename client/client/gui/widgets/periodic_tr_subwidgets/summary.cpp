#include "summary.h"
#include "ui_summary.h"


const QString Summary::stepMessage = "Summary";
const bool Summary::backButton = true;
const bool Summary::confButton = true;
const QString Summary::backMessage = "And Change Some Data";
const QString Summary::confMessage = "And Proceed the Transfer";



Summary::Summary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Summary)
{
    ui->setupUi(this);
    ui->errorLabel->close();
    ui->overflowError->close();
}

Summary::~Summary() { delete ui;  }


void Summary::setCardNumber(QString n) {
    ui->accountConfLabel->setText(n);
}

void Summary::setName(QString n) {
    ui->nameConfLabel->setText(n);
}

void Summary::setSum(int s) {
    ui->sumConfLabel->setText(QString::number(s)+" UAH");
}

void Summary::setStartDate(QDate d) {
    ui->startDateConfLabel->setText(d.toString("dd.MM.yyyy"));
}

void Summary::setFrequency(Frequency f) {
    switch(f) {
    case week:
        ui->freqConfLabel->setText("Once in a week");
        break;
    case month:
        ui->freqConfLabel->setText("Once in a month");
        break;
    case quarter:
        ui->freqConfLabel->setText("Once in a quarter");
        break;
    case year:
        ui->freqConfLabel->setText("Once in a year");
        break;
    default:
        break;
    }

}

void Summary::removeStartDate() {
    ui->startDateConfLabel->close();
    ui->startDateLabel->close();
}

void Summary::removeFrequency() {
    ui->freqConfLabel->close();
    ui->freqLabel->close();
}

void Summary::showError() {
    ui->errorLabel->show();
}

void Summary::closeError() {
    ui->errorLabel->close();
}

void Summary::showOverflowError() {
    ui->overflowError->show();
}

void Summary::closeOverflowError() {
    ui->overflowError->close();
}

