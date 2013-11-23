#include "supportwidget.h"
#include "ui_supportwidget.h"

SupportWidget::SupportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupportWidget)
{
    ui->setupUi(this);
}

SupportWidget::~SupportWidget()
{
    delete ui;
}
