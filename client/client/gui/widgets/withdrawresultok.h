#ifndef WITHDRAWRESULTOK_H
#define WITHDRAWRESULTOK_H

#include <QWidget>

namespace Ui {
class WithdrawResultOk;
}

class WithdrawResultOk : public QWidget
{
    Q_OBJECT

signals:
    void backToSumInput();
    void withdrawalCompleted();

public:
    explicit WithdrawResultOk(QWidget *parent = 0);
    ~WithdrawResultOk();
    const int getSum() const { return _sum; }
    void setSum(const int sum);
    void showError(const int code);

private slots:
    void on_backButton_clicked();
    void on_withdrawButton_clicked();
    void on_actionCompleted();

private:
    Ui::WithdrawResultOk *ui;
    int _sum;
};

#endif // WITHDRAWRESULTOK_H
