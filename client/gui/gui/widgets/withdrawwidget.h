#ifndef WITHDRAWWIDGET_H
#define WITHDRAWWIDGET_H

#include <QWidget>

namespace Ui {
class WithdrawWidget;
}

class WithdrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WithdrawWidget(QWidget *parent = 0);
    ~WithdrawWidget();

private:
    Ui::WithdrawWidget *ui;
};

#endif // WITHDRAWWIDGET_H
