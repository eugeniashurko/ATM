#ifndef PERIODICTR_STEP1_H
#define PERIODICTR_STEP1_H

#include <QWidget>

namespace Ui {
class PeriodicTr_Step1;
}

class PeriodicTr_Step1 : public QWidget
{
    Q_OBJECT

public:
    explicit PeriodicTr_Step1(QWidget *parent = 0);
    ~PeriodicTr_Step1();

private:
    Ui::PeriodicTr_Step1 *ui;
};

#endif // PERIODICTR_STEP1_H
