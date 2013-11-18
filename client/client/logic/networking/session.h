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
    const QString getToken() const {return _token; }
    const QString getCard() const {return _card; }
private:
    QString _token;
    QString _card;
};

#endif // SESSION_H
