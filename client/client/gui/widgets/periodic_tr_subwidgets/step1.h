#ifndef STEP1_H
#define STEP1_H

#include <QWidget>

namespace Ui {
class Step1;
}

class Step1 : public QWidget
{
    Q_OBJECT

public:
    explicit Step1(QWidget *parent = 0);
    ~Step1();

private:
    Ui::Step1 *ui;
};

#endif // STEP1_H
