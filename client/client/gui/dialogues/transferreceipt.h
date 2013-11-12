#ifndef TRANSFERRECEIPT_H
#define TRANSFERRECEIPT_H

#include <QDialog>

namespace Ui {
class TransferReceipt;
}

class TransferReceipt : public QDialog
{
    Q_OBJECT

public:
    explicit TransferReceipt(QWidget *parent = 0);
    ~TransferReceipt();

private slots:
    void on_farewellOkButton_clicked();

private:
    Ui::TransferReceipt *ui;
};

#endif // TRANSFERRECEIPT_H
