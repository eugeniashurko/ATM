#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QString>

class ConnectionManager
{
private:
//    // verification token
//    QString token;

//    // server IP
//    static const QString server = "37.139.13.175";

//    // urls defined in API
//    static const QString AUTH_URL = "/api/auth/";

//    static const QString BALANCE_URL = "/api/balance/";

//    static const QString WITHDRAW_URL = "/api/withdraw/";
//    // ...

public:
    ConnectionManager();
    ~ConnectionManager() {}
    // connection methods
    void connect();
//    void disconnect();
//    bool checkConnection();
//    // requests methods
//    void authRequest(QString card, QString PIN);
//    void balanceRequest(QString card);
//    void withdrawalRequest(QString card, int sum);

};

#endif // CONNECTIONMANAGER_H
