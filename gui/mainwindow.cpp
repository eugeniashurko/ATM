#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
//    start(new StartWidget(this)),
//    auth(new AuthWidget(this)),
//    farewell(new FarewellWidget(this)),
//    menu(new MenuWidget(this))
{
    //this->layout()->
    ui->setupUi(this);
//    QObject::connect(start, SIGNAL(on_InsertCardButton_clicked()), this, SLOT(performAuth()));
//    auth->hide();
//    farewell->hide();
//    menu ->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_exitButton_clicked()
//{

//    setCentralWidget(farewell);
//    QThread::sleep(3);
//    setCentralWidget(start);
//    this->performExit();
//}

//void MainWindow::performExit() {
//    farewell = new FarewellWidget(this);
//    setCentralWidget(farewell);
//    QThread::sleep(6);
//    performStart();
//    setCentralWidget(start);
//    setCentralWidget(start);
//}

//void MainWindow::createActions()
//{
//    QAction * newAct = new QAction(tr("Exit"), this);
//    newAct->setStatusTip(tr("Exit"));
//    connect(newAct, SIGNAL(activated()), this, SLOT(performExit()));
//}

//void MainWindow::performAuth() {
//    start->hide();
//    auth->show();
//}
