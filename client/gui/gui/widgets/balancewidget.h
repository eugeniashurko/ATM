#ifndef BALANCEWIDGET_H
#define BALANCEWIDGET_H

#include <QWidget>

namespace Ui {
class BalanceWidget;
}

class BalanceWidget : public QWidget
{
    Q_OBJECT
public slots:
   void on_withdrawButton_clicked();

signals:
   void fromBalanceWithdrawCalled();

public:
    explicit BalanceWidget(QWidget *parent = 0);
    ~BalanceWidget();

private:
    Ui::BalanceWidget *ui;
};

#endif // BALANCEWIDGET_H
