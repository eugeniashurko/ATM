#ifndef TRANSFERRECEIPT_H
#define TRANSFERRECEIPT_H

#include <QDialog>

#include "../widgets/periodic_tr_subwidgets/summary.h"


namespace Ui {
class TransferReceipt;
}

class TransferReceipt : public QDialog
{
    Q_OBJECT

signals:
    void periodicTransferComplete(TransferReceipt *);

public:
    explicit TransferReceipt(QWidget *parent = 0);
    ~TransferReceipt();
    void setName(QString name);
    void setCard(QString card);
    void setSum(int sum);
    void setStartDate(QDate d);
    void setFrequency(Frequency f);
    void removeStartDate();
    void removeFrequency();

private slots:
    void on_farewellOkButton_clicked();

private:
    Ui::TransferReceipt *ui;
};

#endif // TRANSFERRECEIPT_H
