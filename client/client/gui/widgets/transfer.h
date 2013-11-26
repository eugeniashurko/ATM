#ifndef TRANSFER_H
#define TRANSFER_H

#include <QStackedWidget>
#include <QStack>
#include <QWidget>
#include <QDebug>

#include "periodic_tr_subwidgets/step1.h"
#include "periodic_tr_subwidgets/step2.h"
#include "periodic_tr_subwidgets/step3.h"
#include "periodic_tr_subwidgets/summary.h"
#include "../dialogues/transferreceipt.h"
#include "../../logic/networking/connectionmanager.h"
#include "../../logic/networking/session.h"

namespace Ui {
class Transfer;
}

class Transfer : public QWidget
{
    Q_OBJECT
signals:
    void changeStackedWidgetIndex(int);
    void prevStepCalled();
    void dataReceived(int);
    void cardNumberReceived(QString);
    void sumReceived(int);
    void currentWChanged(int, bool);
    void completeCalled();
    void transferCompleted();
    void checkReceiverCardCalled(const QString& card);
    void cardInputSuccess(bool);
    void checkBalanceCalled(QString);
    void transferPerformCalled(QString, QString, QString);

private slots:
    void on_confirmButton_clicked();
    void on_backButton_clicked();
    void initializeStep(int i);

    void setCardNumber(QString c) { rec_card = c; }
    void setName(QString n) { rec_name = n; }
    void setSum(int s) { sum = s; }

    void saveData(int);

    void on_checkReceiverCardFailure();
    void on_checkReceiverCardSuccess(QString name);

    void on_checkBalanceFailure();
    void on_checkBalanceSuccess();

    void on_insufficientFunds();

public:
    explicit Transfer(QWidget *parent = 0);
    ~Transfer();

private:
    Ui::Transfer *ui;
    QStackedWidget * stack;

    // Attributes of transfer - need to be remembered
    QString rec_card;
    QString rec_name;
    int sum;

    bool card_ok;
    bool sum_ok;
};

#endif // TRANSFER_H
