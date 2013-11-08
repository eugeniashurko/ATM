#ifndef WITHDRAWALRECEIPT_H
#define WITHDRAWALRECEIPT_H

#include <QDialog>

namespace Ui {
class WithdrawalReceipt;
}

class WithdrawalReceipt : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawalReceipt(QWidget *parent = 0);
    ~WithdrawalReceipt();

private:
    Ui::WithdrawalReceipt *ui;
};

#endif // WITHDRAWALRECEIPT_H
