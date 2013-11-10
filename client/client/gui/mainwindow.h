#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

//#include "widgets/startwidget.h"
//#include "widgets/authwidget.h"
//#include "widgets/menuwidget.h"
//#include "widgets/farewellwidget.h"

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
    void initialize();
    void callMenu();
    void on_exitButton_clicked();
    void on_authPerformed(QString, QString);
    void on_insertClick();
    void on_balancePerformed();
    void on_withdrawPerformed();
    void on_periodicTrPerformed();
    void on_sumProvided(int);
    void on_toMainMenuButton_clicked();

    void customSumInput();

private:
    void switchWidgetTo(QWidget* w);
    Ui::MainWindow * ui;
    QWidget *current_widget;
};

#endif // MAINWINDOW_H
