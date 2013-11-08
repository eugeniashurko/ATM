#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>

namespace Ui {
class AuthWidget;
}

class AuthWidget : public QWidget
{
    Q_OBJECT

signals:
    void authCalled(QString, QString);

private slots:
    void on_authButton_clicked();

public:
    explicit AuthWidget(QWidget *parent = 0);
    ~AuthWidget();

private:
    Ui::AuthWidget *ui;

};

#endif // AUTHWIDGET_H
