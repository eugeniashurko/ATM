#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QMainWindow>


namespace Ui {
    class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();

private slots:
    void on_InsertCardButton_clicked();

signals:
    void authCalled();

private:
    Ui::StartWidget *ui;
};


//namespace Ui {
//class StartWidget;
//}

//class StartWidget : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit StartWidget(QWidget *parent = 0);
//    ~StartWidget();

//private slots:
//    void on_InsertCardButton_clicked();

//private:
//    Ui::StartWidget *ui;
//};

#endif // STARTWIDGET_H
