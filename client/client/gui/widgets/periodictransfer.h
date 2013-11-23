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
    void dataReceived(int);
    void cardNumberReceived(QString);
    //void nameRecieved(QString);
    void sumReceived(int);
    void startDateReceived(const QDate);
    void frequencyReceived(Frequency);
    void completeCalled();
    void periodicTrCompleted();


private slots:
    void on_confirmButton_clicked();
    void on_backButton_clicked();
    void initializeStep(int i);

    void setCardNumber(QString c) { rec_card = c; }
    void setName(QString n) { rec_name = n; }
    void setSum(int s) { sum = s; }
    void setStartDate(QDate d) { start_date = d; }
    void setFrequency(Frequency f) { freq = f; }

    void saveData(int);

    void performComplete();
    void on_actionCompleted(TransferReceipt *);


public:
    explicit PeriodicTransfer(QString card = "",
                              QString name = "",
                              double s = 0,
                              Frequency fr = week,
                              QDate d = QDate::currentDate(),
                              QWidget * parent = 0);
    ~PeriodicTransfer();

private:    
    Ui::PeriodicTransfer * ui;
    QStackedWidget * stack;

    // Attributes of periodic transfer - need to be remembered
    QString rec_card;
    QString rec_name;
    int sum;
    Frequency freq;
    QDate start_date;

};

#endif // PERIODICTRANSFER_H
