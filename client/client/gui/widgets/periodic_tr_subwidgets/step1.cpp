#include "step1.h"
#include "ui_step1.h"

#include <QDebug>

const QString Step1::stepMessage = "Step 1: Step  Receiving Account Number";
const bool Step1::backButton = false;
const bool Step1::confButton = true;
const QString Step1::backMessage = "";
const QString Step1::confMessage = "";


Step1::Step1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step1)
{
    ui->setupUi(this);
    ui->errorLabel->close();
    ui->invalidLabel->close();
}

const QString Step1::getCardNumber() {
   return ui->cardNumberInput->text();
}

Step1::~Step1() {  delete ui; }

void Step1::showError() {
    ui->invalidLabel->close();
    ui->errorLabel->show();
}

void Step1::closeError() {
    ui->errorLabel->close();
}

void Step1::showInvalid() {
    ui->errorLabel->close();
    ui->invalidLabel->show();
}

void Step1::closeInvalid() {
    ui->invalidLabel->close();
}
