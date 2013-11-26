#include "pinreminddialogue.h"
#include "ui_pinreminddialogue.h"

PinRemindDialogue::PinRemindDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinRemindDialogue),
    _pin("")
{
    ui->setupUi(this);
    ui->errorLabel->close();
}

PinRemindDialogue::~PinRemindDialogue()
{
    delete ui;
}

void PinRemindDialogue::on_okButton_clicked() {
    _pin = ui->pinInput->text();
    emit okCalled(_pin);
}

void PinRemindDialogue::showError() {
    ui->errorLabel->show();
}


void PinRemindDialogue::on_reAuthFailed() {
    showError();
}

void PinRemindDialogue::on_reAuthSuccess() {
    this->close();
}

void PinRemindDialogue::on_finishButton_clicked()
{
    close();
    emit exitCalled();
}
