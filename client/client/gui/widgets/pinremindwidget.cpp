#include "pinremindwidget.h"
#include "ui_pinremindwidget.h"

PinRemindWidget::PinRemindWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinRemindWidget),
    _pin("")
{
    ui->setupUi(this);
    ui->errorLabel->close();
}

PinRemindWidget::~PinRemindWidget()
{
    delete ui;
}

void PinRemindWidget::on_okButton_clicked() {
    _pin = ui->pinInput->text();
    emit okCalled();
}

void PinRemindWidget::showError() {
    ui->errorLabel->show();
}
