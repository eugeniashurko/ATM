#ifndef SESSION_H
#define SESSION_H

#include <QObject>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QString token, QString card, QObject *parent = 0);
    ~Session();
signals:

public slots:
    void setToken(QString token);

private:
    QString _token;
    QString _card;
};

#endif // SESSION_H
