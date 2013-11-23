#include "farewelldialogue.h"
#include "ui_farewelldialogue.h"

FarewellDialogue::FarewellDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FarewellDialogue)
{
    ui->setupUi(this);
}

FarewellDialogue::~FarewellDialogue()
{
    delete ui;
}

void FarewellDialogue::on_farewellOkButton_clicked()
{
    this->close();
    emit okClicked(this);
}
