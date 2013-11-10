#ifndef WITHDRAWWIDGET_H
#define WITHDRAWWIDGET_H

#include <QWidget>

namespace Ui {
class WithdrawWidget;
}

class WithdrawWidget : public QWidget
{
    Q_OBJECT
signals:
    void customSumInputCalled();
    void sum(int);

public:
    explicit WithdrawWidget(QWidget *parent = 0);
    ~WithdrawWidget();

private slots:
    void on_sum20Button_clicked();
    void on_sum50Button_clicked();
    void on_sum100Button_clicked();
    void on_sum200Button_clicked();
    void on_sum500Button_clicked();
    void on_sumCustomButton_clicked();

private:
    Ui::WithdrawWidget *ui;
};

#endif // WITHDRAWWIDGET_H
