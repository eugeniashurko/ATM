#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    start(new StartWidget()),
    current(start)
{
    ui->setupUi(this);
    setCentralWidget(start);
}

MainWindow::~MainWindow()
{
    delete ui;
}
