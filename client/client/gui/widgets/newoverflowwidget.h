#ifndef NEWOVERFLOWWIDGET_H
#define NEWOVERFLOWWIDGET_H

#include <QWidget>
#include <QStackedWidget>


namespace Ui {
class NewOverflowWidget;
}

class NewOverflowWidget : public QWidget
{
    Q_OBJECT
signals:
    void changeStackedWidgetIndex(int);
    void prevStepCalled();
    void dataReceived(int);
    void cardNumberReceived(QString);
    void sumReceived(int);

    void checkReceiverCardCalled(const QString& card);
    void cardInputSuccess(bool);
    void settingsCalled(QString, QString, QString);

private slots:
    void on_confirmButton_clicked();
    void on_backButton_clicked();
    void initializeStep(int i);

    void setCardNumber(QString c) { _card = c; }
    void setName(QString n) { _name = n; }
    void setSum(int s) { _max_sum = s; }

    void saveData(int);

    void on_checkReceiverCardFailure();
    void on_checkReceiverCardSuccess(QString name);

public slots:
    void on_overflowFailure();

public:
    explicit NewOverflowWidget(const QString& card, QWidget *parent = 0);
    ~NewOverflowWidget();

private:
    Ui::NewOverflowWidget *ui;
    QStackedWidget * stack;

    QString sender_card;
    QString _card;
    QString _name;
    double _max_sum;

    bool card_ok;
    bool sum_ok;
    bool sum_nice;
};

#endif // NEWOVERFLOWWIDGET_H
