#ifndef STEP1_H
#define STEP1_H

#include <QWidget>
#include <QString>


namespace Ui {
    class Step1;
}

class Step1 : public QWidget
{
    Q_OBJECT
public:
    explicit Step1(QWidget *parent = 0);
    ~Step1();

    static const QString stepMessage;
    static const bool backButton;
    static const bool confButton;
    static const QString backMessage;
    static const QString confMessage;
    const QString getCardNumber();
    void showError();
    void closeError();
    void showInvalid();
    void closeInvalid();

private:
    Ui::Step1 * ui;

};

#endif // STEP1_H
