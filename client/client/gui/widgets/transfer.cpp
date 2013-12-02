#include "transfer.h"
#include "ui_transfer.h"
#include "../../logic/utils/Validate.h"


Transfer::Transfer(QString card, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer),
    stack(new QStackedWidget),
    sender_card(card),
    rec_card(""),
    rec_name(""),
    sum(0),
    card_ok(false),
    sum_ok(false)
{
    ui->setupUi(this);
    Step1 * s1 = new Step1;
    Step2 * s2 = new Step2;
    Step3 * s3 = new Step3;
    Summary * s = new Summary;
    stack->addWidget(s1);
    stack->addWidget(s2);
    stack->addWidget(s3);
    stack->addWidget(s);
    ui->mainLayout->addWidget(stack);
    connect(this, SIGNAL(changeStackedWidgetIndex(int)), stack, SLOT(setCurrentIndex(int)) );
    connect(stack, SIGNAL(currentChanged(int)), this, SLOT(initializeStep(int)));
    initializeStep(0);
}

Transfer::~Transfer()
{
    delete ui;
    delete stack;
}


void Transfer::initializeStep(int prev)
{
    stack->setCurrentIndex(prev);
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
            message = Summary::stepMessage;
            cB = Summary::confButton;
            bB = Summary::backButton;
            cM = Summary::confMessage;
            bM = Summary::backMessage;
            Summary * s = static_cast<Summary *>(stack->currentWidget());
            s->setCardNumber(rec_card);
            s->setName(rec_name);
            s->setSum(sum);
            s->removeStartDate();
            s->removeFrequency();
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

void Transfer::on_confirmButton_clicked()
{
    if (stack->currentIndex() < 3) {
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
        default:
            emit changeStackedWidgetIndex(stack->currentIndex()+1);
            break;
        }
    } else {
        emit transferPerformCalled(rec_card, rec_name, QString::number(sum));
    }
}

void Transfer::on_backButton_clicked()
{
    emit changeStackedWidgetIndex(stack->currentIndex()-1);
}

void Transfer::saveData(int source) {
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
    case 1:
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
            break;
        }
    default:
        break;
    }
}

void Transfer::on_checkReceiverCardFailure() {
    (static_cast<Step1 *>(stack->currentWidget()))->showError();
}

void Transfer::on_checkReceiverCardSuccess(QString name) {
    rec_name = name;
    card_ok = true;
}

void Transfer::on_checkBalanceFailure() {
    (static_cast<Step3 *>(stack->currentWidget()))->showError();
}

void Transfer::on_checkBalanceSuccess() {
    sum_ok = true;
}

void Transfer::on_insufficientFunds() {
    static_cast<Summary *>(stack->currentWidget())->showError();
}
