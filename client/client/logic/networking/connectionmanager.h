#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class ConnectionManager : public QObject
{
    Q_OBJECT

public:

    // Networking problems exceptions class
    class BadConnection {
    private:
        QString msg;
    public:
        BadConnection(QString reason = "Some networking problems occured!"): msg(reason) {}
        ~BadConnection() {}
        QString reason() { return msg; }
    };

    // Token expired exception
    class TokenExpired {
    public:
        TokenExpired() {}
        ~TokenExpired() {}
    };

    explicit ConnectionManager(QObject *parent = 0);
    ~ConnectionManager();

    bool checkConnection();

    // Request methods:

    // Returns token if successful
    QString authRequest(QString card, QString PIN);

    // Returns balance if successful
    // Throws exception if not authorized
    // Throws exception if network error
    const int balanceRequest(QString token);

//    void withdrawalRequest(QString card, int sum);



private:
    QNetworkAccessManager * manager;
    // ssl configurations should be set to every request
    QSslConfiguration * config;

    // host address and port
    static const QString HOST;
    static const QString PORT;

    // urls defined in API
    static const QString GREET_URL;
    static const QString AUTH_URL;
    static const QString BALANCE_URL;
    static const QString WITHRAW_URL;
    static const QString TRANSFER_URL;
    static const QString PERIODIC_URL;
    static const QString OVERFLOW_URL;


};

#endif // CONNECTIONMANAGER_H
