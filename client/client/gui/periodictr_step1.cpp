#include "periodictr_step1.h"
#include "ui_periodictr_step1.h"

PeriodicTr_Step1::PeriodicTr_Step1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeriodicTr_Step1)
{
    ui->setupUi(this);
}

PeriodicTr_Step1::~PeriodicTr_Step1()
{
    delete ui;
}
