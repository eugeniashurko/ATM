#include "farewellwidget.h"
#include "ui_farewellwidget.h"

FarewellWidget::FarewellWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FarewellWidget)
{
    ui->setupUi(this);
}

FarewellWidget::~FarewellWidget()
{
    delete ui;
}
