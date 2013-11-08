#include <QThread>
#include <QAction>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/startwidget.h"
#include "widgets/authwidget.h"
#include "widgets/menuwidget.h"
#include "widgets/balancewidget.h"
#include "widgets/withdrawwidget.h"
#include "widgets/periodictransfer.h"

#include "dialogues/farewelldialogue.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_widget(0)
{
    ui->setupUi(this);
    initialize();
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
    return;
}

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
    //current_widget->move(ui->verticalLayoutWidget->geometry().center());
    return;
}

void MainWindow::on_insertClick()
{
    AuthWidget* w = new AuthWidget;
    connect(w, SIGNAL(authCalled(QString, QString)), this, SLOT(on_authPerformed(QString, QString)));
    switchWidgetTo(w);
    return;
}

void MainWindow::callMenu() {
    MenuWidget* w = new MenuWidget;
    connect(w, SIGNAL(balanceCalled()), this, SLOT(on_balancePerformed()));
    connect(w, SIGNAL(withdrawCalled()), this, SLOT(on_withdrawPerformed()));
    connect(w, SIGNAL(periodicTrCalled()), this, SLOT(on_periodicTrPerformed()));
    switchWidgetTo(w);
}

void MainWindow::on_authPerformed(QString a, QString b)
{
     qDebug() << a;
     qDebug() << b;
     callMenu();
}

void MainWindow::on_balancePerformed() {
    BalanceWidget *w = new BalanceWidget;
    connect(w, SIGNAL(fromBalanceWithdrawCalled()), this, SLOT(on_withdrawPerformed()));
    switchWidgetTo(w);
}

void MainWindow::on_withdrawPerformed() {
    WithdrawWidget *w = new WithdrawWidget;
    switchWidgetTo(w);
}

void MainWindow::on_periodicTrPerformed() {
    PeriodicTransfer *w = new PeriodicTransfer;
    switchWidgetTo(w);
}

void MainWindow::on_exitButton_clicked()
{
    FarewellDialogue * d = new FarewellDialogue;
    d->show();
    initialize();
}


void MainWindow::on_toMainMenuButton_clicked()
{
    callMenu();
}
