#include <QDebug>
#include <iostream>
#include "periodictransfer.h"

#include "../dialogues/transferreceipt.h"

#include "../../logic/utils/Validate.h"

PeriodicTransfer::PeriodicTransfer(QString card,
                                   QWidget * parent) :
    QWidget(parent),
    ui(new Ui::PeriodicTransfer),
    stack(new QStackedWidget),
    sender_card(card),
    rec_card(""),
    rec_name(""),
    sum(0),
    freq(week),
    start_date(QDate::currentDate()),
    card_ok(false),
    sum_ok(false),
    date_ok(false)
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
    initializeStep(0);
}

PeriodicTransfer::~PeriodicTransfer()
{
    delete ui;
    delete stack;
}

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
            static_cast<Step1 *>(stack->currentWidget())->closeError();
            static_cast<Step1 *>(stack->currentWidget())->closeInvalid();
        }
        break;

    case 1:
        {
            message = Step2::stepMessage;
            cB = Step2::confButton;
            bB = Step2::backButton;
            cM = Step2::confMessage;
            bM = Step2::backMessage;
            static_cast<Step2 *>(stack->currentWidget())->setAccount(rec_card);
            static_cast<Step2 *>(stack->currentWidget())->setName(rec_name);
        }
        break;

    case 2:
        {
            message = Step3::stepMessage;
            cB = Step3::confButton;
            bB = Step3::backButton;
            cM = Step3::confMessage;
            bM = Step3::backMessage;
            static_cast<Step3 *>(stack->currentWidget())->closeError();
            static_cast<Step3 *>(stack->currentWidget())->closeInvalid();
        }
        break;
    case 3:
        {
            message = Step4::stepMessage;
            cB = Step4::confButton;
            bB = Step4::backButton;
            cM = Step4::confMessage;
            bM = Step4::backMessage;
            static_cast<Step4 *>(stack->currentWidget())->closeDateError();
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
            s->closeError();
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
        saveData(stack->currentIndex());
        switch(stack->currentIndex()) {
        case 0:
            if (card_ok) {
                emit changeStackedWidgetIndex(stack->currentIndex()+1);
            }
            break;
        case 2:
            if (sum_ok) {
                emit changeStackedWidgetIndex(stack->currentIndex()+1);
            }
            break;
        case 3:
            if (date_ok) {
                emit changeStackedWidgetIndex(stack->currentIndex()+1);
            }
            break;
        default:
            emit changeStackedWidgetIndex(stack->currentIndex()+1);
            break;
        }
    } else {
        emit periodicTransferPerformCalled(rec_card, rec_name, QString::number(sum),
                                           freq, start_date);
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
            QString card = static_cast<Step1 *>(stack->currentWidget())->getCardNumber();
            if (validLog(card.toStdString()) && (card != sender_card)) {
                emit checkReceiverCardCalled(card);
                rec_card = card;
            } else {
                static_cast<Step1 *>(stack->currentWidget())->showInvalid();
            }
        }
        break;
    case 2:
        {
            QString isum = static_cast<Step3 *>(stack->currentWidget())->getAccumulator();
            if ((isum != "") && (isum.toInt() != 0)) {
                emit checkBalanceCalled(isum);
                sum = isum.toInt();
            } else {
                static_cast<Step3 *>(stack->currentWidget())->showInvalid();
            }
        }
        break;
    case 3:
        {
            QDate date = static_cast<Step4 *>(stack->currentWidget())->getStartDate();
            Frequency f = static_cast<Step4 *>(stack->currentWidget())->getFrequency();
            if (date >= QDate::currentDate()) {
                date_ok = true;
                start_date = date;
                freq = f;
            } else {
                static_cast<Step4 *>(stack->currentWidget())->showDateError();
            }

         }
        break;
     default:
        break;
    }
}

void PeriodicTransfer::on_checkReceiverCardFailure() {
    (static_cast<Step1 *>(stack->currentWidget()))->showError();
}

void PeriodicTransfer::on_checkReceiverCardSuccess(QString name) {
    rec_name = name;
    card_ok = true;
}

void PeriodicTransfer::on_checkBalanceFailure() {
    (static_cast<Step3 *>(stack->currentWidget()))->showError();
}

void PeriodicTransfer::on_checkBalanceSuccess() {
    sum_ok = true;
}

void PeriodicTransfer::on_insufficientFunds() {
    static_cast<Summary *>(stack->currentWidget())->showError();
}

