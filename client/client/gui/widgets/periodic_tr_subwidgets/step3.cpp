#include "step3.h"
#include "ui_step3.h"

#include <QDebug>

const QString Step3::stepMessage = "Step 3: Sum of Transfer";
const bool Step3::backButton = true;
const bool Step3::confButton = true;
const QString Step3::backMessage = "";
const QString Step3::confMessage = "";


Step3::Step3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step3),
    acc("")
{
    ui->setupUi(this);
    connect(this, SIGNAL(input(QString)), this, SLOT(addToAccumulator(QString)));
}

Step3::~Step3() {  delete ui; }

void Step3::on_num1Button_clicked()
{
    emit input("1");
}

void Step3::on_num2Button_clicked()
{
     emit input("2");
}

void Step3::on_num3Button_clicked()
{
    emit input("3");
}

void Step3::on_num4Button_clicked()
{
    emit input("4");
}

void Step3::on_num5Button_clicked()
{
    emit input("5");
}

void Step3::on_num6Button_clicked()
{
    emit input("6");
}

void Step3::on_num7Button_clicked()
{
    emit input("7");
}

void Step3::on_num8Button_clicked()
{
    emit input("8");
}

void Step3::on_num9Button_clicked()
{
    emit input("9");
}

void Step3::on_num0Button_clicked()
{
    emit input("0");

}

void Step3::on_editButton_clicked()
{
    acc = acc.mid(0, acc.length()-1);
    if (acc != "")
        ui->inputSumLabel->setText(acc + "  UAH");
    else
        ui->inputSumLabel->setText("0  UAH");

}

void Step3::on_cleanButton_clicked()
{
    acc = "";
    ui->inputSumLabel->setText("0  UAH");
}

void Step3::addToAccumulator(QString input) {
    acc += input;
    ui->inputSumLabel->setText(acc + "  UAH");
}

const int Step3::getAccumulator() const {
    return acc.toInt();
}
