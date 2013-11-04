#ifndef FAREWELLWIDGET_H
#define FAREWELLWIDGET_H

#include <QWidget>

namespace Ui {
class FarewellWidget;
}

class FarewellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FarewellWidget(QWidget *parent = 0);
    ~FarewellWidget();

private:
    Ui::FarewellWidget *ui;
};

#endif // FAREWELLWIDGET_H
