#include "servererror.h"
#include "ui_servererror.h"

ServerError::ServerError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerError)
{
    ui->setupUi(this);
}

ServerError::~ServerError()
{
    delete ui;
}

void ServerError::on_finishButton_clicked()
{
    close();
    emit exitCalled();
}

void ServerError::on_backButton_clicked()
{
    close();
    emit backCalled();
}
