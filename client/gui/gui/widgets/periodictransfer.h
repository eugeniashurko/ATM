#ifndef PERIODICTRANSFER_H
#define PERIODICTRANSFER_H

#include <QWidget>


namespace Ui {
class PeriodicTransfer;
}

class PeriodicTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit PeriodicTransfer(QWidget *parent = 0);
    ~PeriodicTransfer();

    void goToStep(QWidget * w,
                  QString desc,
                  bool back,
                  bool confirm,
                  QString back_msg,
                  QString conf_msg);

private:
    Ui::PeriodicTransfer *ui;
    QWidget * current_widget;
};

#endif // PERIODICTRANSFER_H
