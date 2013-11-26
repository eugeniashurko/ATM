#include "newoverflowwidget.h"
#include "ui_newoverflowwidget.h"
#include "periodic_tr_subwidgets/step1.h"
#include "periodic_tr_subwidgets/step2.h"
#include "periodic_tr_subwidgets/step3.h"
#include "periodic_tr_subwidgets/summary.h"


NewOverflowWidget::NewOverflowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewOverflowWidget),
    stack(new QStackedWidget)
{
    ui->setupUi(this);
    stack->addWidget(new Step1);
    stack->addWidget(new Step2);
    stack->addWidget(new Step3);
    stack->addWidget(new Summary);
    ui->mainLayout->addWidget(stack);
    connect(this, SIGNAL(changeStackedWidgetIndex(int)), stack, SLOT(setCurrentIndex(int)) );
    connect(stack, SIGNAL(currentChanged(int)), this, SLOT(initializeStep(int)));
    connect(this, SIGNAL(dataReceived(int)), this, SLOT(saveData(int)));
    connect(this, SIGNAL(completeCalled()), this, SLOT(performComplete()));
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
            s2->setAccount(_card);
            // ! Here we get from database account's owner name !
            // ! and set it as rec_name
            s2->setName(_name);
        }
        break;
    case 2:
        {
            message = "Step 3: Set the maximum sum on your account";
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
        emit dataReceived(stack->currentIndex());
        emit changeStackedWidgetIndex(stack->currentIndex()+1);
    } else {
        emit completeCalled();
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
            Step1 * s1 = dynamic_cast<Step1 *>(stack->currentWidget());
            _card = s1->getCardNumber();
            // card number validation
        }
        break;

    case 2:
        {
            Step3 * s3 = dynamic_cast<Step3 *>(stack->currentWidget());
            _max_sum = s3->getAccumulator().toDouble();
            // balance sufficiency validation
        }
        break;
     default:
        break;
    }
}

void NewOverflowWidget::performComplete() {
    emit settingsCompleted();
}



