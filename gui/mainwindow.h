#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "startwidget.h"
#include "authwidget.h"
#include "menuwidget.h"
#include "farewellwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void on_exitButton_clicked();


public slots:
//    void performExit();
//    void performAuth();
//    void performInput();
//    void performAuth();
//    void performMenu();

private:
    Ui::MainWindow * ui;
//    StartWidget * start;
//    AuthWidget * auth;
//    MenuWidget * menu;
//    FarewellWidget * farewell;

//    void createActions();
//    QWidget * current;
};

#endif // MAINWINDOW_H
