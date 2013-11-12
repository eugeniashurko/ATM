#ifndef SUPPORTWIDGET_H
#define SUPPORTWIDGET_H

#include <QWidget>

namespace Ui {
class SupportWidget;
}

class SupportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SupportWidget(QWidget *parent = 0);
    ~SupportWidget();

private:
    Ui::SupportWidget *ui;
};

#endif // SUPPORTWIDGET_H
