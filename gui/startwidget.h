#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>

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
    void on_InsertCardButton_pressed();

private:
    Ui::StartWidget *ui;
};

#endif // STARTWIDGET_H
