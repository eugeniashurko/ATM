#ifndef SERVERERRORWIDGET_H
#define SERVERERRORWIDGET_H

#include <QWidget>

namespace Ui {
class ServerErrorWidget;
}

class ServerErrorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerErrorWidget(QWidget *parent = 0);
    ~ServerErrorWidget();

private:
    Ui::ServerErrorWidget *ui;
};

#endif // SERVERERRORWIDGET_H
