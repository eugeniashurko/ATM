#include <QDebug>
#include <iostream>
#include "periodictransfer.h"

#include "../dialogues/transferreceipt.h"


PeriodicTransfer::PeriodicTransfer(QString card,
                                   QString name,
                                   double su,
                                   Frequency fr,
                                   QDate d,
                                   QWidget * parent) :
    QWidget(parent),
    ui(new Ui::PeriodicTransfer),
    stack(new QStackedWidget),
    rec_card(card),
    rec_name(name),
    sum(su),
    freq(fr),
    start_date(d)
{
    ui->setupUi(this);
    Step1 * s1 = new Step1;
    Step2 * s2 = new Step2;
    Step3 * s3 = new Step3;
    Step4 * s4 = new Step4;
    Summary * s = new Summary;
    stack->addWidget(s1);
    stack->addWidget(s2);
    stack->addWidget(s3);
    stack->addWidget(s4);
    stack->addWidget(s);
    ui->mainLayout->addWidget(stack);
    connect(this, SIGNAL(changeStackedWidgetIndex(int)), stack, SLOT(setCurrentIndex(int)) );
    connect(stack, SIGNAL(currentChanged(int)), this, SLOT(initializeStep(int)));
    connect(this, SIGNAL(dataReceived(int)), this, SLOT(saveData(int)));
    connect(this, SIGNAL(completeCalled()), this, SLOT(performComplete()));
    initializeStep(0);
}

PeriodicTransfer::~PeriodicTransfer()
{
    delete ui;
    delete stack;
}


// ! PUT ALIDATION HERE SOMEHOW !
void PeriodicTransfer::initializeStep(int prev)
{
    QString message;
    bool cB;
    bool bB;
    QString cM;
    QString bM;
    switch(prev) {
    case 0:
        {
            message = Step1::stepMessage;
            cB = Step1::confButton;
            bB = Step1::backButton;
            cM = Step1::confMessage;
            bM = Step1::backMessage;
        }
        break;

    case 1:
        {
            message = Step2::stepMessage;
            cB = Step2::confButton;
            bB = Step2::backButton;
            cM = Step2::confMessage;
            bM = Step2::backMessage;
            Step2 * s2 = dynamic_cast<Step2 *>(stack->currentWidget());
            s2->setAccount(rec_card);
            // ! Here we get from database account's owner name !
            // ! and set it as rec_name
            s2->setName(rec_name);
        }
        break;

    case 2:
        {
            message = Step3::stepMessage;
            cB = Step3::confButton;
            bB = Step3::backButton;
            cM = Step3::confMessage;
            bM = Step3::backMessage;
        }
        break;
    case 3:
        {
            message = Step4::stepMessage;
            cB = Step4::confButton;
            bB = Step4::backButton;
            cM = Step4::confMessage;
            bM = Step4::backMessage;
         }
        break;
     case 4:
        {
            message = Summary::stepMessage;
            cB = Summary::confButton;
            bB = Summary::backButton;
            cM = Summary::confMessage;
            bM = Summary::backMessage;
            Summary * s = dynamic_cast<Summary *>(stack->currentWidget());
            s->setCardNumber(rec_card);
            s->setName(rec_name);
            s->setSum(sum);
            s->setStartDate(start_date);
            s->setFrequency(freq);
        }
        break;
     default:
        break;
    }

    ui->stepDescrLabel->setText(message);
    ui->backButton->setEnabled(bB);
    ui->confirmButton->setEnabled(cB);
    ui->backLabel->setText(bM);
    ui->confLabel->setText(cM);
}

void PeriodicTransfer::on_confirmButton_clicked()
{
    if (stack->currentIndex() < 4) {
        emit dataReceived(stack->currentIndex());
        emit changeStackedWidgetIndex(stack->currentIndex()+1);
    } else {
        emit completeCalled();
    }
}

void PeriodicTransfer::on_backButton_clicked()
{
    emit changeStackedWidgetIndex(stack->currentIndex()-1);
}

void PeriodicTransfer::saveData(int source) {
    switch(source) {
    case 0:
        {
            Step1 * s1 = dynamic_cast<Step1 *>(stack->currentWidget());
            rec_card = s1->getCardNumber();
            // card number validation
        }
        break;

    case 2:
        {
            Step3 * s3 = dynamic_cast<Step3 *>(stack->currentWidget());
            sum = s3->getAccumulator().toInt();
            // balance sufficiency validation
        }
        break;
    case 3:
        {
            Step4 * s4 = dynamic_cast<Step4 *>(stack->currentWidget());
            start_date = s4->getStartDate();
            freq = s4->getFrequency();
            // time validation
         }
        break;
     default:
        break;
    }
}

void PeriodicTransfer::performComplete() {
    TransferReceipt * d = new TransferReceipt;
    d->setWindowTitle("Periodic Transfer Receipt");
    d->setName(this->rec_name);
    d->setCard(this->rec_card);
    d->setSum(this->sum);
    d->setStartDate(this->start_date);
    d->setFrequency(this->freq);
    d->setModal(true);
    d->show();
    connect(d, SIGNAL(periodicTransferComplete(TransferReceipt *)),
            this, SLOT(on_actionCompleted(TransferReceipt *)));
 }

void PeriodicTransfer::on_actionCompleted(TransferReceipt * d) {
    delete d;
    d = 0;
    emit periodicTrCompleted();
}

