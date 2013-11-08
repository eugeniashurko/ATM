#include "step3.h"
#include "ui_step3.h"

Step3::Step3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step3)
{
    ui->setupUi(this);
}

Step3::~Step3()
{
    delete ui;
}
