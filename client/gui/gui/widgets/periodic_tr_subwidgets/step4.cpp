#include "step4.h"
#include "ui_step4.h"

Step4::Step4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step4)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Once in a week");
    ui->comboBox->addItem("Once in a month");
    ui->comboBox->addItem("Once in a quarter");
    ui->comboBox->addItem("Once in a year");
}

Step4::~Step4()
{
    delete ui;
}
