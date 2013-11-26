#ifndef PINREMINDDIALOGUE_H
#define PINREMINDDIALOGUE_H

#include <QDialog>

#include "../../logic/networking/connectionmanager.h"

namespace Ui {
class PinRemindDialogue;
}

class PinRemindDialogue : public QDialog
{
    Q_OBJECT


signals:
    void okCalled(QString);
    void exitCalled();

private slots:
    void on_okButton_clicked();

    void on_finishButton_clicked();

public slots:
    void showError();
    void on_reAuthFailed();

    void on_reAuthSuccess();

public:
    explicit PinRemindDialogue(QWidget *parent = 0);
    ~PinRemindDialogue();

private:
    Ui::PinRemindDialogue *ui;
    QString _pin;
};


#endif // PINREMINDDIALOGUE_H
