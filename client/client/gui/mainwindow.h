#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../logic/networking/session.h"
#include "../logic/networking/connectionmanager.h"
#include "../logic/utils/LogFile.h"
#include "../logic/teller.h"

#include "dialogues/servererror.h"
#include "dialogues/farewelldialogue.h"
#include "widgets/withdrawresultok.h"
#include "widgets/periodictransfer.h"



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
    void insufficientFunds();
    void settingsCompleted();
    void cleanOverflowSuccessfull();
    void SumWasInvalid();
    void overflowFailure();

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
    void makeWithdrawal(const int, WithdrawResultOk * widget);

    // transfer util-methods
    void on_checkReceiverCard(QString card);
    void on_checkBalance(QString sum);
    void makeTransfer(QString, QString, QString);

    // periodic tarnsfer util-methods
    void makePeriodicTransfer(QString, QString, QString, Frequency, QDate);

    void on_cleanOverflowSetting();
    void on_newOverflow();
    void setOverflow(QString, QString, QString);

private:
    // util methods
    void switchWidgetTo(QWidget* w);
    void pinRemind();

    Ui::MainWindow * ui;
    QWidget * current_widget;
    ServerError * error;
    Session * session;
    ConnectionManager * connection;
    Teller * teller;
};

#endif // MAINWINDOW_H
