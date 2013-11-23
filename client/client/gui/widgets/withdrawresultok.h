#ifndef WITHDRAWRESULTOK_H
#define WITHDRAWRESULTOK_H

#include <QWidget>
#include "../dialogues/withdrawalreceipt.h"


namespace Ui {
class WithdrawResultOk;
}

class WithdrawResultOk : public QWidget
{
    Q_OBJECT

signals:
    void backToSumInput();
    void withdraw(const double,  WithdrawResultOk * widget);

public:
    explicit WithdrawResultOk(QWidget *parent = 0);
    ~WithdrawResultOk();
    int getSum() const { return _sum; }
    void setSum(const double sum);
    void showError(const int code);

private slots:
    void on_backButton_clicked();
    void on_withdrawButton_clicked();

private:
    Ui::WithdrawResultOk *ui;
    double _sum;
};

#endif // WITHDRAWRESULTOK_H
