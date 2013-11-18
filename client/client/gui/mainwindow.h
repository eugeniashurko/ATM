#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../logic/networking/session.h"
#include "../logic/networking/connectionmanager.h"
#include "dialogues/servererror.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void pinRemind(bool* ok, const bool after_error=false);
    void tryBalance();
private slots:
    void initialize();
    void callMenu();
    void cleanError();
    void invokeServerError();
    void on_exitButton_clicked();
    void on_authPerformed(QString, QString);
    void on_insertClick();
    void on_balancePerformed();
    void on_withdrawPerformed();
    void on_periodicTrPerformed();
    void on_sumProvided(int);
    void on_toMainMenuButton_clicked();
    void on_transferPerformed();
    void on_supportPerformed();

    void customSumInput();

private:
    void switchWidgetTo(QWidget* w);
    Ui::MainWindow * ui;
    QWidget * current_widget;
    ServerError * error;
    Session * session;
    ConnectionManager * connection;
};

#endif // MAINWINDOW_H
