#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <list>

class ConnectionManager : public QObject
{
    Q_OBJECT

public:

    // Networking problems exceptions
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

    // Thrown in auth-request if account does not exist
    class AuthFailed {
    public:
        AuthFailed() {}
        ~AuthFailed() {}
    };

    explicit ConnectionManager(QObject *parent = 0);
    ~ConnectionManager();

    // Function for checking the connection
    bool checkConnection();

    // REQUEST METHODS:

    // Makes authentication request by card and pin
    // - returns session token if successful
    // - throws ConnectionManager::BadConnection exception in case of connection troubles
    // - throws ConnectionManager::AuthFailed if account does not exist
    QString authRequest(QString card, QString PIN);

    // Makes balance inquiry request
    // - returns balance if successful
    // - throws ConnectionManager::BadConnection exception in case of connection troubles
    // - throws ConnectionManager::TokenExpired in case of time out
    const std::list<int> balanceRequest(QString token);

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