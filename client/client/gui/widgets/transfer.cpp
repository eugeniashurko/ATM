#include "transfer.h"
#include "ui_transfer.h"

#include "../dialogues/transferreceipt.h"

Transfer::Transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer),
    stack(new QStackedWidget()),
    rec_card("00000000000000000"),
    rec_name("Jon Snow"),
    sum(0)
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
    connect(this, SIGNAL(dataReceived(int)), this, SLOT(saveData(int)));
    connect(this, SIGNAL(completeCalled()), this, SLOT(performComplete()));
    initializeStep(0);
}

Transfer::~Transfer()
{
    delete ui;
    delete stack;
}

// ! PUT FUCKIN VALIDATION HERE SOMEHOW !
void Transfer::initializeStep(int prev)
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
            message = Summary::stepMessage;
            cB = Summary::confButton;
            bB = Summary::backButton;
            cM = Summary::confMessage;
            bM = Summary::backMessage;
            Summary * s = dynamic_cast<Summary *>(stack->currentWidget());
            s->setCardNumber(rec_card);
            s->setName(rec_name);
            s->setSum(sum);
            s->removeStartDate();
            s->removeFrequency();
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
        emit dataReceived(stack->currentIndex());
        emit changeStackedWidgetIndex(stack->currentIndex()+1);
    } else {
        emit completeCalled();
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
            Step1 * s1 = dynamic_cast<Step1 *>(stack->currentWidget());
            rec_card = s1->getCardNumber();
            // card number validation
        }
        break;

    case 2:
        {
            Step3 * s3 = dynamic_cast<Step3 *>(stack->currentWidget());
            sum = s3->getAccumulator();
            // balance sufficiency validation
        }
        break;
     default:
        break;
    }
}

void Transfer::performComplete() {
    TransferReceipt * d = new TransferReceipt;
    connect(d, SIGNAL(periodicTransferComplete()), this, SLOT(on_actionCompleted()));
    d->setWindowTitle("Transfer Receipt");
    d->setName(this->rec_name);
    d->setCard(this->rec_card);
    d->setSum(this->sum);
    d->removeStartDate();
    d->removeFrequency();
    d->setModal(true);
    d->show();
 }

void Transfer::on_actionCompleted() {
     emit transferCompleted();
}


