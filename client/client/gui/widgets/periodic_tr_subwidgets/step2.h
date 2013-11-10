#ifndef STEP2_H
#define STEP2_H

#include <QWidget>

namespace Ui {
    class Step2;
}

class Step2 : public QWidget
{
    Q_OBJECT
public:
    explicit Step2(QWidget *parent = 0);
    ~Step2();

    static const QString stepMessage;
    static const bool backButton;
    static const bool confButton;
    static const QString backMessage;
    static const QString confMessage;

    void setName(QString);
    void setAccount(QString);

private:
    Ui::Step2 * ui;
};

#endif // STEP2_H
