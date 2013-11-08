#include "authwidget.h"
#include "ui_authwidget.h"

AuthWidget::AuthWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthWidget)
{
    ui->setupUi(this);
    connect(ui->authButton, SIGNAL(clicked()), this, SLOT(on_authButton_clicked()));
}

AuthWidget::~AuthWidget()
{
    delete ui;
}

void AuthWidget::on_authButton_clicked()
{
    // Check input
    emit authCalled(ui->cadNumberInput->text(), ui->pinInput->text());
}
