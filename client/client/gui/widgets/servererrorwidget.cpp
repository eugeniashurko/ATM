#include "servererrorwidget.h"
#include "ui_servererrorwidget.h"

ServerErrorWidget::ServerErrorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerErrorWidget)
{
    ui->setupUi(this);
}

ServerErrorWidget::~ServerErrorWidget()
{
    delete ui;
}
