#include "step1.h"
#include "ui_step1.h"

Step1::Step1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step1)
{
    ui->setupUi(this);
}

Step1::~Step1()
{
    delete ui;
}
