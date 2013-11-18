#ifndef FAREWELLDIALOGUE_H
#define FAREWELLDIALOGUE_H

#include <QDialog>

namespace Ui {
class FarewellDialogue;
}

class FarewellDialogue : public QDialog
{
    Q_OBJECT
signals:
   void okClicked();

public:
    explicit FarewellDialogue(QWidget *parent = 0);
    ~FarewellDialogue();

private slots:
    void on_farewellOkButton_clicked();

private:
    Ui::FarewellDialogue *ui;
};

#endif // FAREWELLDIALOGUE_H
