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
signals:

private slots:
    void openConnection();


public:
    explicit ConnectionManager(QObject *parent = 0);
    void sslError(const QList<QSslError> &errors);
    ~ConnectionManager() {}



//    void disconnect();
//    bool checkConnection();
//    // requests methods
//    void authRequest(QString card, QString PIN);
//    void balanceRequest(QString card);
//    void withdrawalRequest(QString card, int sum);

private slots:
   // void replyFinished(QNetworkReply*);

private:
    QUrl * url;
    QNetworkAccessManager *manager;
    QSslConfiguration * config;

    // urls defined in API
    static const QString AUTH_URL;
    static const QString BALANCE_URL;
    static const QString WITHDRAW_URL;
    // ...

};

#endif // CONNECTIONMANAGER_H
