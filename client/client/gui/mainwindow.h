#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../logic/networking/session.h"
#include "../logic/networking/connectionmanager.h"
#include "dialogues/servererror.h"
#include "dialogues/farewelldialogue.h"
#include "widgets/withdrawresultok.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void checkReceiverFailure();
    void checkReceiverSuccess(const QString&);
    void reAuthFialed();
    void reAuthSuccess();
    void checkBalanceSuccess();
    void checkBalanceFailure();

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void tryReAuth(QString);
    // slot util-methods
    void initialize();
    void reinitialize(FarewellDialogue *);
    void callMenu();
    void cleanError();
    void invokeServerError();

    // upper-menu slots
    void on_exitButton_clicked();
    void on_toMainMenuButton_clicked();

    void on_insertClick();
    void on_authFromMenu(QString, QString);

    void on_balanceFromMenu();
    void on_withdrawFromMenu();
    void on_periodicTrFromMenu();
    void on_transferFromMenu();
    void on_overflowFromMenu();
    void on_supportFromMenu();

    // withdrawal util-methods
    void on_sumProvided(int);
    void customSumInput();
    void makeWithdrawal(const double, WithdrawResultOk * widget);

    // transfer util-methods
    void on_checkReceiverCard(QString card);
    void on_checkBalance(QString sum);

    void on_newOverflow();

private:
    // util methods
    void switchWidgetTo(QWidget* w);
    void pinRemind();

    Ui::MainWindow * ui;
    QWidget * current_widget;
    ServerError * error;
    Session * session;
    ConnectionManager * connection;
};

#endif // MAINWINDOW_H
