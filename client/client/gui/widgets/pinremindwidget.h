#ifndef PINREMINDWIDGET_H
#define PINREMINDWIDGET_H

#include <QWidget>

namespace Ui {
class PinRemindWidget;
}

class PinRemindWidget : public QWidget
{
    Q_OBJECT
signals:
    void okCalled();

private slots:
    void on_okButton_clicked();

public slots:
    void showError();
    const QString getPin() { return _pin; }
public:
    explicit PinRemindWidget(QWidget *parent = 0);
    ~PinRemindWidget();

private:
    Ui::PinRemindWidget *ui;
    QString _pin;
};

#endif // PINREMINDWIDGET_H
