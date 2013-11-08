#include "startwidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    connect(ui->InsertCardButton, SIGNAL(clicked()), this, SIGNAL(authCalled()));
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::on_InsertCardButton_clicked()
{
   emit authCalled();
}

