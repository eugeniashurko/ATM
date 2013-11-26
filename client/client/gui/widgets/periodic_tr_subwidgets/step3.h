#ifndef STEP3_H
#define STEP3_H

#include <QWidget>

namespace Ui {
class Step3;
}

class Step3 :  public QWidget
{
    Q_OBJECT

signals:
    void input(QString);
    void editCalled();
    void cleanCalled();

public:
    explicit Step3(QWidget * parent = 0);
    ~Step3();

    static const QString stepMessage;
    static const bool backButton;
    static const bool confButton;
    static const QString backMessage;
    static const QString confMessage;
    void showError();

private slots:
    void on_num1Button_clicked();
    void on_num2Button_clicked();
    void on_num3Button_clicked();
    void on_num4Button_clicked();
    void on_num5Button_clicked();
    void on_num6Button_clicked();
    void on_num7Button_clicked();
    void on_num8Button_clicked();
    void on_num9Button_clicked();
    void on_num0Button_clicked();
    void on_editButton_clicked();
    void on_cleanButton_clicked();

    void addToAccumulator(QString);

public slots:
    QString getAccumulator() const;

private:
    Ui::Step3 * ui;
    QString acc;
};

#endif // STEP3_H
