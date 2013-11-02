#include "authwidget.h"
#include "ui_authwidget.h"

AuthWidget::AuthWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthWidget)
{
    ui->setupUi(this);
}

AuthWidget::~AuthWidget()
{
    delete ui;
}
