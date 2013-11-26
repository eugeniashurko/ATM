#include "transfer.h"
#include "ui_transfer.h"

Transfer::Transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer),
    stack(new QStackedWidget),
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
    connect(this, SIGNAL(dataReceived(int)),
            this, SLOT(saveData(int)));
    connect(this, SIGNAL(completeCalled()),
            this, SLOT(performComplete()));
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
        saveData(stack->currentIndex());
        if ((stack->currentIndex() != 0) || (card_ok)) {
            if ((stack->currentIndex() != 2) || (sum_ok)) {
                emit changeStackedWidgetIndex(stack->currentIndex()+1);
            }
        }
//        qDebug() << stack->currentIndex();
//        emit dataReceived(stack->currentIndex());
//        if (stack->currentIndex() != 0) {
//            emit changeStackedWidgetIndex(stack->currentIndex()+1);
//        }
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
            emit checkReceiverCardCalled(s1->getCardNumber());
            rec_card = s1->getCardNumber();
            // card number validation
        }
        break;
    case 1:
        break;
    case 2:
        {
            Step3 * s3 = dynamic_cast<Step3 *>(stack->currentWidget());
            emit checkBalanceCalled(s3->getAccumulator());
            sum = s3->getAccumulator().toInt();
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

void Transfer::performComplete() {
    TransferReceipt * d = new TransferReceipt;
    connect(d, SIGNAL(periodicTransferComplete(TransferReceipt *)),
            this, SLOT(on_actionCompleted(TransferReceipt *)));
    d->setWindowTitle("Transfer Receipt");
    d->setName(this->rec_name);
    d->setCard(this->rec_card);
    d->setSum(this->sum);
    d->removeStartDate();
    d->removeFrequency();
    d->setModal(true);
    d->show();
 }

void Transfer::on_actionCompleted(TransferReceipt * d) {
    delete d;
    emit transferCompleted();
}

void Transfer::on_checkReceiverCardFailure() {
    qDebug() << "Failure received";
    (static_cast<Step1 *>(stack->currentWidget()))->showError();
}

void Transfer::on_checkReceiverCardSuccess(QString name) {
    qDebug() << "Success received and sent";
    rec_name = name;
    card_ok = true;
}

void Transfer::on_checkBalanceFailure() {
    qDebug() << "Failure received";
    (static_cast<Step3 *>(stack->currentWidget()))->showError();
}

void Transfer::on_checkBalanceSuccess() {
    qDebug() << "Success received and sent";
    sum_ok = true;
}
