#include "step2.h"
#include "ui_step2.h"

Step2::Step2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step2)
{
    ui->setupUi(this);
}

Step2::~Step2()
{
    delete ui;
}
