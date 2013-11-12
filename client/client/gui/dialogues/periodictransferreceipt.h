#ifndef PERIODICTRANSFERRECEIPT_H
#define PERIODICTRANSFERRECEIPT_H

#include <QDialog>

namespace Ui {
class PeriodicTransferReceipt;
}

class PeriodicTransferReceipt : public QDialog
{
    Q_OBJECT

public:
    explicit PeriodicTransferReceipt(QWidget *parent = 0);
    ~PeriodicTransferReceipt();

private:
    Ui::PeriodicTransferReceipt *ui;
};

#endif // PERIODICTRANSFERRECEIPT_H
