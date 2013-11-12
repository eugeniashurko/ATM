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
    connect(ui->transferButton, SIGNAL(clicked()), this, SLOT(on_transferButton_clicked()) );

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

void MenuWidget::on_transferButton_clicked() {
    emit transferCalled();
}


void MenuWidget::on_supportButton_clicked()
{
    emit supportCalled();
}
