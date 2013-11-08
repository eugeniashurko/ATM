#include "periodictransfer.h"
#include "ui_periodictransfer.h"
#include "periodic_tr_subwidgets/step1.h"
#include "periodic_tr_subwidgets/step2.h"
#include "periodic_tr_subwidgets/step3.h"
#include "periodic_tr_subwidgets/step4.h"
#include "periodic_tr_subwidgets/summary.h"

PeriodicTransfer::PeriodicTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeriodicTransfer),
    current_widget(0)
{
    ui->setupUi(this);
    //Step1 * s1 = new Step1;
    //Step2 *s2 = new Step2;
    Step3 *s3 = new Step3;
    //Step4 *s4 = new Step4;
    //Summary *ss = new Summary;
    //connect(s, SIGNAL(authCalled()), this, SLOT(on_insertClick()));
    //goToStep(s1, "Step 1: Receiving Account Number", false, true, "", "");
    //goToStep(s2, "Step 2: Confirm the Receiver", true, true, "Change Account", "");
    goToStep(s3, "Step 3: Sum of Transfer", true, true, "", "");
    //goToStep(s4, "Step 4: Time Preferences", true, true, "", "");
    //goToStep(ss, "Summary: ", true, true, "", "Proceed the Transfer");
}

PeriodicTransfer::~PeriodicTransfer()
{
    delete ui;
}

void PeriodicTransfer::goToStep(QWidget * w,
                                QString desc,
                                bool back,
                                bool conf,
                                QString back_msg,
                                QString conf_msg)
{

    delete current_widget;
    current_widget = w;
    ui->mainLayout->addWidget(w);

    ui->stepDescrLabel->setText(desc);
    if (!back)
        ui->backButton->close();
    if (!conf)
        ui->confirmButton->close();
    ui->backLabel->setText(back_msg);
    ui->confLabel->setText(conf_msg);
}
