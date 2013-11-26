#include "customsuminput.h"
#include "ui_customsuminput.h"

#include <QDebug>

CustomSumInput::CustomSumInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomSumInput),
    input(new Step3)
{
    ui->setupUi(this);
    ui->mainLayout->addWidget(input);
}

CustomSumInput::~CustomSumInput()
{
    delete ui;
}

void CustomSumInput::on_confirmButton_clicked()
{
    emit sumProvided(input->getAccumulator().toInt());
}
