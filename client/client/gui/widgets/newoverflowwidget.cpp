#include "newoverflowwidget.h"
#include "ui_newoverflowwidget.h"
#include "periodic_tr_subwidgets/step1.h"
#include "periodic_tr_subwidgets/step2.h"
#include "periodic_tr_subwidgets/step3.h"
#include "periodic_tr_subwidgets/summary.h"

#include "../../logic/utils/Validate.h"


NewOverflowWidget::NewOverflowWidget(const QString& c, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewOverflowWidget),
    stack(new QStackedWidget),
    sender_card(c),
    _card(""),
    _name(""),
    _max_sum(0),
    card_ok(false),
    sum_ok(false)
{
    ui->setupUi(this);
    stack->addWidget(new Step1);
    stack->addWidget(new Step2);
    stack->addWidget(new Step3);
    stack->addWidget(new Summary);
    ui->mainLayout->addWidget(stack);
    connect(this, SIGNAL(changeStackedWidgetIndex(int)), stack, SLOT(setCurrentIndex(int)) );
    connect(stack, SIGNAL(currentChanged(int)), this, SLOT(initializeStep(int)));
    initializeStep(0);
}

NewOverflowWidget::~NewOverflowWidget()
{
    delete ui;
    delete stack;
}

void NewOverflowWidget::initializeStep(int prev)
{
    QString message;
    bool cB;
    bool bB;
    QString cM;
    QString bM;
    switch(prev) {
    case 0:
        {
            message = "Step 1: Set supplementary account number";
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
            static_cast<Step2 *>(stack->currentWidget())->setAccount(_card);
            static_cast<Step2 *>(stack->currentWidget())->setName(_name);
        }
        break;
    case 2:
        {
            message = "Step 3: Set the maximum sum on your account";
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
            Summary * s = dynamic_cast<Summary *>(stack->currentWidget());
            s->setCardNumber(_card);
            s->setName(_name);
            s->setSum(_max_sum);
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

void NewOverflowWidget::on_confirmButton_clicked()
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
        emit settingsCalled(_card, _name, QString::number(_max_sum));
    }
}


void NewOverflowWidget::on_backButton_clicked()
{
    emit changeStackedWidgetIndex(stack->currentIndex()-1);
}

void NewOverflowWidget::saveData(int source) {
    switch(source) {
    case 0:
        {
            QString card = static_cast<Step1 *>(stack->currentWidget())->getCardNumber();
            if (validLog(card.toStdString()) && (card != sender_card)) {
                emit checkReceiverCardCalled(card);
                _card = card;
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
              _max_sum = isum.toInt();
              sum_ok = true;
            } else {
                static_cast<Step3 *>(stack->currentWidget())->showInvalid();
            }
        }
     default:
        break;
    }
}




void NewOverflowWidget::on_checkReceiverCardFailure() {
    (static_cast<Step1 *>(stack->currentWidget()))->showError();
}

void NewOverflowWidget::on_checkReceiverCardSuccess(QString name) {
    _name = name;
    card_ok = true;
}
