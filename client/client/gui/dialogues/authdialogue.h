#ifndef AUTHDIALOGUE_H
#define AUTHDIALOGUE_H

#include <QDialog>

namespace Ui {
class AuthDialogue;
}

class AuthDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialogue(QWidget *parent = 0);
    ~AuthDialogue();

private:
    Ui::AuthDialogue *ui;
};

#endif // AUTHDIALOGUE_H
