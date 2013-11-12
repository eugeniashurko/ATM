#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public slots:
    void on_balanceButton_clicked();
    void on_withdrawButton_clicked();
    void on_transferButton_clicked();
    void on_periodicTrButton_clicked();
    //void on_overflowButton_clicked();


signals:
    void balanceCalled();
    void withdrawCalled();
    void transferCalled();
    void periodicTrCalled();
    //void overflowCalled();
    void supportCalled();

public:
    explicit MenuWidget(QWidget *parent = 0);
    ~MenuWidget();


private slots:
    void on_supportButton_clicked();

private:
    Ui::MenuWidget *ui;
};

#endif // MENUWIDGET_H
