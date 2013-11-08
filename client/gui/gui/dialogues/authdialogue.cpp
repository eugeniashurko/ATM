#include "authdialogue.h"
#include "ui_authdialogue.h"

AuthDialogue::AuthDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialogue)
{
    ui->setupUi(this);
}

AuthDialogue::~AuthDialogue()
{
    delete ui;
}
