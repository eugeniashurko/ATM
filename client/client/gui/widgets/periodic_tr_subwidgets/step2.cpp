#include "step2.h"
#include "ui_step2.h"

const QString Step2::stepMessage = "Step 2: Confirm the Receiver";
const bool Step2::backButton = true;
const bool Step2::confButton = true;
const QString Step2::backMessage = "";
const QString Step2::confMessage = "";


Step2::Step2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step2)
{
    ui->setupUi(this);
}

Step2::~Step2() { delete ui; }

void Step2::setAccount(QString n) {
    ui->accountConfLabel->setText(n);
}

void Step2::setName(QString n) {
    ui->nameConfLabel->setText(n);
}
