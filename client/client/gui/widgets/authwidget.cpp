#include "authwidget.h"
#include "ui_authwidget.h"
#include "../../logic/utils/Validate.h"

AuthWidget::AuthWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthWidget)
{
    ui->setupUi(this);
    connect(ui->authButton, SIGNAL(clicked()), this, SLOT(on_authButton_clicked()));
    ui->errorLabel->setText("Authentication failed!");
    ui->errorLabel->close();
}

AuthWidget::~AuthWidget()
{
    delete ui;
}

void AuthWidget::on_authButton_clicked()
{
    if (!validLog(ui->cadNumberInput->text().toStdString())) {
        ui->errorLabel->setText("Invalid card number!");
        ui->errorLabel->show();
    } else if (!validPin(ui->pinInput->text().toStdString())) {
        ui->errorLabel->setText("Invalid PIN!");
        ui->errorLabel->show();
    } else {
        emit authCalled(ui->cadNumberInput->text(), ui->pinInput->text());
    }
}

void AuthWidget::showError() {
    ui->errorLabel->show();
}

void AuthWidget::on_pinInput_returnPressed()
{
    on_authButton_clicked();
}
