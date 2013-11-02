#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "startwidget.h"
#include "authwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setStart() { current = start; }
    void setAuth() { current = auth; }


private:
    Ui::MainWindow * ui;
    StartWidget * start;
    AuthWidget * auth;
    QWidget * current;
};

#endif // MAINWINDOW_H
