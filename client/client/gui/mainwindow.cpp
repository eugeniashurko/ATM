#include <QThread>
#include <QAction>
#include <QDebug>
#include <iostream>

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
#include "widgets/withdrawresultok.h"
#include "widgets/transfer.h"
#include "widgets/supportwidget.h"

#include "dialogues/farewelldialogue.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_widget(0)
{
    ui->setupUi(this);
    this->setWindowTitle("ATM");
    initialize();
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
    return;
}

// Service functions
void MainWindow::initialize() {
    StartWidget* a = new StartWidget;
    connect(a, SIGNAL(authCalled()), this, SLOT(on_insertClick()));
    switchWidgetTo(a);
    return;
}

void MainWindow::switchWidgetTo(QWidget* w)
{
    delete current_widget;
    current_widget = w;
    ui->widgetsVerticalLayout->addWidget(w);
    return;
}

void MainWindow::callMenu() {
    MenuWidget* w = new MenuWidget;
    connect(w, SIGNAL(balanceCalled()), this, SLOT(on_balancePerformed()));
    connect(w, SIGNAL(withdrawCalled()), this, SLOT(on_withdrawPerformed()));
    connect(w, SIGNAL(periodicTrCalled()), this, SLOT(on_periodicTrPerformed()));
    connect(w, SIGNAL(transferCalled()), this, SLOT(on_transferPerformed()));
    connect(w, SIGNAL(supportCalled()), this, SLOT(on_supportPerformed()));
    switchWidgetTo(w);
}

// Upper bar buttons
void MainWindow::on_exitButton_clicked()
{
    FarewellDialogue * d = new FarewellDialogue;
    d->setWindowTitle("Reminder");
    d->setModal(true);
    d->show();
    initialize();
}


void MainWindow::on_toMainMenuButton_clicked()
{
    callMenu();
}


// Widgets switching

void MainWindow::on_insertClick()
{
    AuthWidget* w = new AuthWidget;
    connect(w, SIGNAL(authCalled(QString, QString)), this, SLOT(on_authPerformed(QString, QString)));
    switchWidgetTo(w);
    return;
}

void MainWindow::on_authPerformed(QString a, QString b)
{
    // ! CARD/PIN validation here !
    qDebug() << a;
    qDebug() << b;
    callMenu();
}

void MainWindow::on_balancePerformed() {
    BalanceWidget *w = new BalanceWidget;
    connect(w, SIGNAL(fromBalanceWithdrawCalled()), this, SLOT(on_withdrawPerformed()));
    switchWidgetTo(w);
}


void MainWindow::on_periodicTrPerformed() {
    PeriodicTransfer *w = new PeriodicTransfer;
    switchWidgetTo(w);
}


// Withdrawal slots

void MainWindow::on_withdrawPerformed() {
    WithdrawWidget *w = new WithdrawWidget;
    switchWidgetTo(w);
    connect(w, SIGNAL(customSumInputCalled()), this, SLOT(customSumInput()));
    connect(w, SIGNAL(sum(int)), this, SLOT(on_sumProvided(int)));
}

void MainWindow::customSumInput() {
    CustomSumInput * w = new CustomSumInput;
    switchWidgetTo(w);
    connect(w, SIGNAL(sumProvided(int)), this, SLOT(on_sumProvided(int)));
}

void MainWindow::on_sumProvided(int sum) {
    // ! Balance sufficiency validation here !
    WithdrawResultOk * w = new WithdrawResultOk;
    connect(w, SIGNAL(backToSumInput()), this, SLOT(on_withdrawPerformed()));
    connect(w, SIGNAL(withdrawalCompleted()), this, SLOT(callMenu()));
    w->setSum(sum);
    switchWidgetTo(w);
    qDebug() << sum;
}

void MainWindow::on_transferPerformed() {
    Transfer * w = new Transfer;
    switchWidgetTo(w);
}

void MainWindow::on_supportPerformed() {
    SupportWidget * w = new SupportWidget;
    switchWidgetTo(w);
}
