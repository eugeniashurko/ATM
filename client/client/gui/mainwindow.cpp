#include <QThread>
#include <QAction>
#include <QDebug>
#include <iostream>
#include <list>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgets/startwidget.h"
#include "widgets/authwidget.h"
#include "widgets/menuwidget.h"
#include "widgets/balancewidget.h"
#include "widgets/withdrawwidget.h"
#include "widgets/periodictransfer.h"
#include "widgets/periodic_tr_subwidgets/step3.h"
#include "widgets/customsuminput.h"
#include "widgets/transfer.h"
#include "widgets/supportwidget.h"
#include "widgets/servererrorwidget.h"
#include "widgets/pinremindwidget.h"
#include "widgets/overflowwidget.h"
#include "widgets/newoverflowwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_widget(0),
    error(0),
    session(0),
    connection(new ConnectionManager)

{
    ui->setupUi(this);
    this->setWindowTitle("ATM");
    initialize();
    return;
}

MainWindow::~MainWindow()
{
    if (error != 0) {
        delete error;
        error = 0;
    }

    delete session;
    session = 0;

    delete connection;
    connection = 0;

    delete current_widget;
    current_widget = 0;

    delete ui;
    ui = 0;

    return;
}

// Service functions
void MainWindow::initialize() {
    ui->toMainMenuButton->close();
    if (connection->checkConnection()) {
        StartWidget* a = new StartWidget;
        connect(a, SIGNAL(authCalled()), this, SLOT(on_insertClick()));
        switchWidgetTo(a);
    } else {
       ServerErrorWidget * w = new ServerErrorWidget;
       switchWidgetTo(w);
    }
    return;
}

void MainWindow::switchWidgetTo(QWidget* w)
{
    if (current_widget != 0) {
        delete current_widget;
        current_widget = 0;
    }
    current_widget = w;
    ui->widgetsVerticalLayout->addWidget(w);
    return;
}

void MainWindow::callMenu() {
    ui->toMainMenuButton->show();
    MenuWidget* w = new MenuWidget;
    connect(w, SIGNAL(balanceCalled()), this, SLOT(on_balanceFromMenu()));
    connect(w, SIGNAL(withdrawCalled()), this, SLOT(on_withdrawFromMenu()));
    connect(w, SIGNAL(periodicTrCalled()), this, SLOT(on_periodicTrFromMenu()));
    connect(w, SIGNAL(transferCalled()), this, SLOT(on_transferFromMenu()));
    connect(w, SIGNAL(supportCalled()), this, SLOT(on_supportFromMenu()));
    connect(w, SIGNAL(overflowCalled()), this, SLOT(on_overflowFromMenu()));
    switchWidgetTo(w);
    return;
}

void MainWindow::cleanError() {
    if (error != 0) {
        delete error;
        error = 0;
    }
    return;
}

void MainWindow::invokeServerError() {
    if (error == 0) {
        error = new ServerError;
        error->setModal(true);
        error->setWindowTitle("Server Connection Error");
        error->show();
        connect(error, SIGNAL(exitCalled()), this, SLOT(on_exitButton_clicked()));
        connect(error, SIGNAL(exitCalled()), this, SLOT(cleanError()));
        connect(error, SIGNAL(backCalled()), this, SLOT(cleanError()));
    }
}

// Upper bar buttons
void MainWindow::on_exitButton_clicked()
{

    // close session here
    if (session != 0) {
        delete session;
        session = 0;
    }

    FarewellDialogue * d = new FarewellDialogue;
    d->setWindowTitle("Reminder");
    d->setModal(true);
    d->show();
    connect(d, SIGNAL(okClicked(FarewellDialogue *)),
            this, SLOT(reinitialize(FarewellDialogue *)));
    return;
}

void MainWindow::reinitialize(FarewellDialogue * d) {
    delete d;
    d = 0;
    initialize();
}

void MainWindow::on_toMainMenuButton_clicked()
{
    callMenu();
    return;
}


// Widgets switching

void MainWindow::on_insertClick()
{
    AuthWidget* w = new AuthWidget;
    ui->toMainMenuButton->close();
    connect(w, SIGNAL(authCalled(QString, QString)), this, SLOT(on_authFromMenu(QString, QString)));
    switchWidgetTo(w);
    return;
}

void MainWindow::on_authFromMenu(QString card, QString pin)
{
    // ! CARD/PIN validation here !
    try {
        QString token = connection->authRequest(card, pin);
        //qDebug() << connection->authRequest(card, pin);
        session = new Session(token, card);
        callMenu();
    }
    catch(ConnectionManager::BadConnection) {
        invokeServerError();
    }
    catch(ConnectionManager::AuthFailed) {
        AuthWidget * w = new AuthWidget;
        ui->toMainMenuButton->close();
        w->showError();
        connect(w, SIGNAL(authCalled(QString, QString)), this, SLOT(on_authFromMenu(QString, QString)));
        switchWidgetTo(w);
    }
    return;
}

void MainWindow::tryBalance() {
    std::list<int> list = connection->balanceRequest(session->getToken());
    BalanceWidget *w = new BalanceWidget(list.front(), list.back());
    connect(w, SIGNAL(fromBalanceWithdrawCalled()), this, SLOT(on_withdrawFromMenu()));
    switchWidgetTo(w);
}

void MainWindow::pinRemind(bool* ok, const bool after_error) {
    PinRemindWidget * w = new PinRemindWidget;
    if (after_error) {
        w->showError();
    }
    switchWidgetTo(w);
    QEventLoop loop;

    connect(w, SIGNAL(okCalled()),
            &loop, SLOT(quit()));
    loop.exec();

    QString pin = w->getPin();
    qDebug() << w->getPin();

    try {
        session->setToken(connection->authRequest(session->getCard(), pin));
        (*ok) = true;
        return;
    }
    catch (ConnectionManager::BadConnection) {
        invokeServerError();
    }
    catch (ConnectionManager::AuthFailed) {
        return;
    }
}

void MainWindow::on_balanceFromMenu() {
    try {
        tryBalance();
    }
    catch(ConnectionManager::BadConnection) {
        invokeServerError();
    }
    catch(ConnectionManager::TokenExpired) {
        bool ok = false;
        pinRemind(&ok, false);
        if (!ok) {
            while (!ok) {
                pinRemind(&ok, true);
            }
            try {
                 tryBalance();
            } catch(ConnectionManager::BadConnection) {
                invokeServerError();
            }
        } else {
            try {
                 tryBalance();
            } catch(ConnectionManager::BadConnection) {
                invokeServerError();
            }
        }

    }
    return;
}


void MainWindow::on_periodicTrFromMenu() {
    PeriodicTransfer *w = new PeriodicTransfer;
    connect(w, SIGNAL(periodicTrCompleted()), this, SLOT(callMenu()));
    switchWidgetTo(w);
    return;
}


// 1. WITHDRAWAL SLOTS

// SLOT Invoked when Withdraw button from Menu is clicked
void MainWindow::on_withdrawFromMenu() {
    WithdrawWidget *w = new WithdrawWidget;
    switchWidgetTo(w);
    connect(w, SIGNAL(customSumInputCalled()), this, SLOT(customSumInput()));
    connect(w, SIGNAL(sum(int)), this, SLOT(on_sumProvided(int)));
    return;
}

// SLOT Invoked when custum sum input called
void MainWindow::customSumInput() {
    CustomSumInput * w = new CustomSumInput;
    switchWidgetTo(w);
    connect(w, SIGNAL(sumProvided(int)), this, SLOT(on_sumProvided(int)));
    return;
}

// SLOT Invokes when sum is provided and the summary (WithdrawResultOk)
// about withdrawal sum is called
void MainWindow::on_sumProvided(int sum) {
    // ! Balance sufficiency validation here !
    WithdrawResultOk * w = new WithdrawResultOk;
    connect(w, SIGNAL(backToSumInput()), this, SLOT(on_withdrawFromMenu()));
    connect(w, SIGNAL(withdraw(const double, WithdrawResultOk *)),
            this, SLOT(makeWithdrawal(const double, WithdrawResultOk *)));
    w->setSum(sum);
    switchWidgetTo(w);
    qDebug() << sum;
    return;
}

// SLOT Invokes when customer confirms withdrawal summary
// actually makes server request and validates all data
void MainWindow::makeWithdrawal(const double sum, WithdrawResultOk * widget) {
    try {
        bool success = true;
        //bool success = connection->withdrawalRequest(session->getToken(), sum);
        if (success) {
            WithdrawalReceipt * d = new WithdrawalReceipt;
            connect(d, SIGNAL(withdrawed(WithdrawalReceipt *)),
                    this, SLOT(callMenu()));
            d->setSum(sum);
            d->setWindowTitle("Withdrawal Receipt");
            d->setModal(true);
            d->show();
        }
        else {
            widget->showError(2);
        }
    }
    catch (ConnectionManager::TokenExpired) {
        bool ok = false;
        pinRemind(&ok, false);
        if (!ok) {
            while (!ok) {
                pinRemind(&ok, true);
            }
            try {
                 tryBalance();
            } catch(...) {
                invokeServerError();
            }
        } else {
            try {
                 tryBalance();
            } catch(...) {
                invokeServerError();
            }
        }
    }
    catch (ConnectionManager::BadConnection) {
        invokeServerError();
    }
}


void MainWindow::on_transferFromMenu() {
    Transfer * w = new Transfer;
    connect(w, SIGNAL(transferCompleted()), this, SLOT(callMenu()));
    switchWidgetTo(w);
    return;
}

void MainWindow::on_overflowFromMenu() {
    OverflowWidget * w = new OverflowWidget;
    connect(w, SIGNAL(cleanCalled()), w, SLOT(setEmpty()));
//    connect(w, SIGNAL(cleanCalled()), this, SLOT(on_cleanOverflowSetting()));
    connect(w, SIGNAL(newOverflowCalled()), this, SLOT(on_newOverflow()));
    // here make request with info and call SetFilled or SetEmpty
    w->setFilled("111111111111", "Tomas Mann", 300);
    switchWidgetTo(w);
    return;
}

void MainWindow::on_newOverflow(){
    NewOverflowWidget * w = new NewOverflowWidget;
    connect(w, SIGNAL(settingsCompleted()), this, SLOT(on_overflowFromMenu()));
    switchWidgetTo(w);
    return;
}

void MainWindow::on_supportFromMenu() {
    SupportWidget * w = new SupportWidget;
    switchWidgetTo(w);
    return;
}
