#ifndef PERIODICTRANSFER_H
#define PERIODICTRANSFER_H

#include <QDateTime>
#include <QStackedWidget>
#include <QStack>
#include <QWidget>

#include "periodictransfer.h"
#include "ui_periodictransfer.h"
#include "periodic_tr_subwidgets/step1.h"
#include "periodic_tr_subwidgets/step2.h"
#include "periodic_tr_subwidgets/step3.h"
#include "periodic_tr_subwidgets/step4.h"
#include "periodic_tr_subwidgets/summary.h"
#include "../dialogues/transferreceipt.h"


namespace Ui {
class PeriodicTransfer;
}

class PeriodicTransfer : public QWidget
{
    Q_OBJECT

signals:
    void changeStackedWidgetIndex(int);
    void prevStepCalled();
    void cardNumberReceived(QString);
    void sumReceived(int);
    void startDateReceived(const QDate);
    void frequencyReceived(Frequency);
    void dataReceived(int);
    void currentWChanged(int, bool);
    void completeCalled();
    void transferCompleted();
    void checkReceiverCardCalled(const QString& card);
    void cardInputSuccess(bool);
    void checkBalanceCalled(QString);
    void periodicTransferPerformCalled(QString, QString, QString, Frequency, QDate);

private slots:
    void setCardNumber(QString c) { rec_card = c; }
    void setName(QString n) { rec_name = n; }
    void setSum(int s) { sum = s; }
    void setStartDate(QDate d) { start_date = d; }
    void setFrequency(Frequency f) { freq = f; }

    void initializeStep(int i);

    void on_confirmButton_clicked();
    void on_backButton_clicked();



    void saveData(int);

    void on_checkReceiverCardFailure();
    void on_checkReceiverCardSuccess(QString name);

    void on_checkBalanceFailure();
    void on_checkBalanceSuccess();

    void on_insufficientFunds();

public:
    explicit PeriodicTransfer(QString card,
                              QWidget * parent = 0);
    ~PeriodicTransfer();

private:    
    Ui::PeriodicTransfer * ui;
    QStackedWidget * stack;

    // Attributes of periodic transfer - need to be remembered
    QString sender_card;
    QString rec_card;
    QString rec_name;
    int sum;
    Frequency freq;
    QDate start_date;

    bool card_ok;
    bool sum_ok;
    bool date_ok;
};

#endif // PERIODICTRANSFER_H
