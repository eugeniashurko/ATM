#ifndef OVERFLOWWIDGET_H
#define OVERFLOWWIDGET_H

#include <QWidget>
#include <QStackedWidget>


namespace Ui {
class OverflowWidget;
}

class OverflowWidget : public QWidget
{
    Q_OBJECT
signals:
    void newOverflowCalled();
    void cleanCalled();

public slots:
    void setEmpty();
    void setFilled(QString card, QString name, double max_sum);

public:
    explicit OverflowWidget(QWidget *parent = 0);
    ~OverflowWidget();

private slots:
    void on_newSettingsButton_clicked();

    void on_cleanButton_clicked();

private:
    Ui::OverflowWidget *ui;
};

#endif // OVERFLOWWIDGET_H
