#ifndef BALANCEWIDGET_H
#define BALANCEWIDGET_H

#include <QWidget>

namespace Ui {
class BalanceWidget;
}

class BalanceWidget : public QWidget
{
    Q_OBJECT

signals:
   void fromBalanceWithdrawCalled();

public:
    explicit BalanceWidget(const int available, const int hold, QWidget *parent = 0);
    ~BalanceWidget();

private slots:
   void on_quickWithdrawalButton_clicked();

private:
    Ui::BalanceWidget *ui;
};

#endif // BALANCEWIDGET_H
