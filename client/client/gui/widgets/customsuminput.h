#ifndef CUSTOMSUMINPUT_H
#define CUSTOMSUMINPUT_H

#include <QWidget>

#include "periodic_tr_subwidgets/step3.h"


namespace Ui {
class CustomSumInput;
}

class CustomSumInput : public QWidget
{
    Q_OBJECT

public:
    explicit CustomSumInput(QWidget *parent = 0);
    ~CustomSumInput();

private slots:
    void on_confirmButton_clicked();

signals:
    void sumProvided(int);

private:
    Ui::CustomSumInput *ui;
    Step3 * input;
};

#endif // CUSTOMSUMINPUT_H
