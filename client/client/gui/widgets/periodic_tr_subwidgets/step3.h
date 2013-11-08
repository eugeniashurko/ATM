#ifndef STEP3_H
#define STEP3_H

#include <QWidget>

namespace Ui {
class Step3;
}

class Step3 : public QWidget
{
    Q_OBJECT

public:
    explicit Step3(QWidget *parent = 0);
    ~Step3();

private:
    Ui::Step3 *ui;
};

#endif // STEP3_H
