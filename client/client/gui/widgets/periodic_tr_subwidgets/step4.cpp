#include "step4.h"
#include "ui_step4.h"

const QString Step4::stepMessage = "Step 4: Time Preferences";
const bool Step4::backButton = true;
const bool Step4::confButton = true;
const QString Step4::backMessage = "";
const QString Step4::confMessage = "";


Step4::Step4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step4)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Once in a week", QVariant("week"));
    ui->comboBox->addItem("Once in a month", QVariant("month"));
    ui->comboBox->addItem("Once in a quarter", QVariant("quarter"));
    ui->comboBox->addItem("Once in a year", QVariant("year"));
}

Step4::~Step4() {  delete ui; }

const QDate Step4::getStartDate() const {
    return ui->calendarWidget->selectedDate();
}

Frequency Step4::getFrequency() const {
    QString selected =ui->comboBox->itemData(ui->comboBox->currentIndex()).toString();
    Frequency res;
    if (selected == "week")
        res = week;
    else if (selected == "month")
        res = month;
    else if (selected == "quarter")
        res = quarter;
    else if (selected == "year")
        res = year;
    return res;
}
