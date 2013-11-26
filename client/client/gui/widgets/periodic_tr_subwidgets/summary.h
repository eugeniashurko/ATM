#ifndef SUMMARY_H
#define SUMMARY_H

#include <QWidget>
#include <QDate>
enum Frequency {week, month, quarter, year};

namespace Ui {
class Summary;
}

class Summary : public QWidget
{
    Q_OBJECT
public:
    explicit Summary(QWidget * parent = 0);
    ~Summary();

    static const QString stepMessage;
    static const bool backButton;
    static const bool confButton;
    static const QString backMessage;
    static const QString confMessage;

    void setCardNumber(QString n);
    void setName(QString n);
    void setSum(int s);
    void setStartDate(QDate d);
    void setFrequency(Frequency f);

    void removeStartDate();
    void removeFrequency();
    void showError();
    void closeError();

private:
    Ui::Summary * ui;
};

#endif // SUMMARY_H
