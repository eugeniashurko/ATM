#ifndef WITHDRAWALRECEIPT_H
#define WITHDRAWALRECEIPT_H

#include <QDialog>

#include "../../logic/banknotecombination.h"

namespace Ui {
class WithdrawalReceipt;
}

class WithdrawalReceipt : public QDialog
{
    Q_OBJECT
signals:
    void withdrawed(WithdrawalReceipt *);

public:
    explicit WithdrawalReceipt(QWidget *parent = 0);
    ~WithdrawalReceipt();
    void setCard(QString c);
    void setSum(const int c);
    void setBankNotes(const BanknoteCombination&);

private slots:
    void on_farewellOkButton_clicked();

private:
    Ui::WithdrawalReceipt *ui;
};

#endif // WITHDRAWALRECEIPT_H
