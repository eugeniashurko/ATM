#ifndef STEP4_H
#define STEP4_H

#include <QWidget>
#include "summary.h"

namespace Ui {
class Step4;
}

class Step4 : public QWidget
{
    Q_OBJECT
public:
    explicit Step4(QWidget * parent = 0);
    ~Step4();

    static const QString stepMessage;
    static const bool backButton;
    static const bool confButton;
    static const QString backMessage;
    static const QString confMessage;

    const QDate getStartDate() const;
    Frequency getFrequency() const;

private:
    Ui::Step4 * ui;
};

#endif // STEP4_H
