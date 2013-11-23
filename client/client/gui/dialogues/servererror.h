#ifndef SERVERERROR_H
#define SERVERERROR_H

#include <QDialog>

namespace Ui {
class ServerError;
}

class ServerError : public QDialog
{
    Q_OBJECT

signals:
    void exitCalled();
    void backCalled();

public:
    explicit ServerError(QWidget *parent = 0);
    ~ServerError();

private slots:
    void on_finishButton_clicked();

    void on_backButton_clicked();

private:
    Ui::ServerError *ui;
};

#endif // SERVERERROR_H
