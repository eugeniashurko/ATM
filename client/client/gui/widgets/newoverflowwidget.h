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
    //void nameRecieved(QString);
    void sumReceived(int);

    void completeCalled();
    void settingsCompleted();

private slots:
    void on_confirmButton_clicked();
    void on_backButton_clicked();
    void initializeStep(int i);

    void setCardNumber(QString c) { _card = c; }
    void setName(QString n) { _name = n; }
    void setSum(int s) { _max_sum = s; }

    void saveData(int);

    void performComplete();


public:
    explicit NewOverflowWidget(QWidget *parent = 0);
    ~NewOverflowWidget();

private:
    Ui::NewOverflowWidget *ui;
    QStackedWidget * stack;

    QString _card;
    QString _name;
    double _max_sum;
};

#endif // NEWOVERFLOWWIDGET_H
