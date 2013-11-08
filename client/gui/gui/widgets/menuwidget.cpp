#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    connect(ui->balanceButton, SIGNAL(clicked()), this, SLOT(on_balanceButton_clicked()) );
    connect(ui->withdrawButton, SIGNAL(clicked()), this, SLOT(on_withdrawButton_clicked()) );
    connect(ui->periodicTrButton, SIGNAL(clicked()), this, SLOT(on_periodicTrButton_clicked()) );

}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::on_balanceButton_clicked() {
   emit balanceCalled();
}

void MenuWidget::on_withdrawButton_clicked() {
    emit withdrawCalled();
}

void MenuWidget::on_periodicTrButton_clicked() {
    emit periodicTrCalled();
}

