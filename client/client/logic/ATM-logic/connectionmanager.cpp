#include "connectionmanager.h"
#include <QSslSocket>
#include <QFile>
#include <QSslKey>
#include <QCoreApplication>


ConnectionManager::ConnectionManager() {}

void ConnectionManager::connect() {

    QSslSocket * socket = new QSslSocket();
    //socket->setSocketDescriptor(handle);
    socket->setProtocol(QSsl::SslV3);

    QByteArray key;
    QByteArray cert;

    QFile file_key("../ssl/client.key");
    if(file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    } else {
        qDebug() << file_key.errorString();
    }

    QFile file_cert("../ssl/client.crt");
    if(file_cert.open(QIODevice::ReadOnly)) {
        cert = file_cert.readAll();
        file_cert.close();
    } else {
        qDebug() << file_cert.errorString();
    }

    QSslKey ssl_key(&key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "password");
    QSslCertificate ssl_cert(cert);
    socket->setPrivateKey(ssl_key);
    socket->setLocalCertificate(ssl_cert);

    socket->connectToHostEncrypted("37.139.13.175", 4443);

    if (!socket->waitForEncrypted()) {
        qDebug() << socket->errorString();
    }

    socket->write("GET /api\nContent-Type: *");

    while (socket->waitForReadyRead())
        qDebug() << socket->readAll().data();
    return;

}

//void ConnectionManager::disconnect() {

//}

//bool ConnectionManager::checkConnection() {

//}

//void ConnectionManager::authRequest(QString card, QString PIN) {
//    QNetworkRequest request;
//    request.setUrl(AUTH_URL);
//    QNetworkReply *reply = manager ->get(request);
//}

//void ConnectionManager::balanceRequest(QString card) {
//    QNetworkRequest request;
//    request.setUrl(BALANCE_URL);
//    QNetworkReply *reply = manager ->get(request);
//}

//void ConnectionManager::withdrawalRequest(QString card, int sum) {
//    QNetworkRequest request;
//    request.setUrl(WITHDRAW_URL);
//    QNetworkReply *reply = manager ->get(request);
//}
