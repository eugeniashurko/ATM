#include "connectionmanager.h"

#include <QFile>
#include <QSslConfiguration>
#include <QUrl>


const QString ConnectionManager::AUTH_URL = "/api/auth/";
const QString ConnectionManager::BALANCE_URL = "/api/balance/";
const QString ConnectionManager::WITHDRAW_URL = "/api/withdraw/";



ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    url(new QUrl),
    manager(new QNetworkAccessManager(this)),
    config(new QSslConfiguration)
{
    url->setHost("37.139.13.175");
    url->setPort(4443);
    qDebug() << url->toEncoded();
//    QFile file( "client.pem" );
//    if( ! file.open( QIODevice::ReadOnly ) )
//    {
//        qDebug() << "cannot open key";
//        return;
//    }
//    QSslKey key(&file, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "password");
//    file.close();
//    config->setPrivateKey(key);
//    config->setLocalCertificate("client.pem");

//    QList expectedSslErrors;

//    foreach( const QSslCertificate &c, cert ) {
//      QSslError error(QSslError::SelfSignedCertificate, c);
//      expectedSslErrors.append(error);
//    }


//    ignoreSslErrors(expectedSslErrors);



//    startServerEncryption();
//    QFile file( "client.crt" );
//    QSslCertificate * cert = QSslCertificate(file,)
//    config->setLocalCertificate(cert);
//    //QSslKey * key = new QSslKey();
//    //config->setPrivateKey();
//    connect(manager, SIGNAL(finished(QNetworkReply*)),
//            this, SLOT(replyFinished(QNetworkReply*)));
}

//void ConnectionManager::sslError( const QList<QSslError> &errors )
//{
//    foreach( const QSslError &error, errors )
//    {
//        if (error.error() != 9)
//        {	   qDebug() << "error";
//          }
//        else
//        {
//            ignoreSslErrors();
//        }
//    }
//}


void ConnectionManager::openConnection() {
    QNetworkRequest * request = new QNetworkRequest(*url);
    request->setSslConfiguration(*config);
    request->setRawHeader("Content-type:", "*");
    manager->get(QNetworkRequest(*request));
}

//    QSslSocket * socket = new QSslSocket();
//    //socket->setSocketDescriptor(handle);
//    socket->setProtocol(QSsl::SslV3);

//    QByteArray key;
//    QByteArray cert;

//    QFile file_key("ssl/client.key");
//    if(file_key.open(QIODevice::ReadOnly)) {
//        key = file_key.readAll();
//        file_key.close();
//    } else   {
//        qDebug() << file_key.errorString();
//    }

//    QFile file_cert("ssl/client.crt");
//    if(file_cert.open(QIODevice::ReadOnly)) {
//        cert = file_cert.readAll();
//        file_cert.close();
//    } else {
//        qDebug() << file_cert.errorString();
//    }

//    QSslKey ssl_key(key, QSsl::Rsa);
//    QSslCertificate ssl_cert(cert);
//    socket->setPrivateKey(ssl_key);
//    socket->setLocalCertificate(ssl_cert);

//    socket->connectToHostEncrypted("37.139.13.175", 4443);

//    if (!socket->waitForEncrypted()) {
//        qDebug() << socket->errorString();
//    }

//    socket->write("GET /api\nContent-Type: *");

//    while (socket->waitForReadyRead())
//        qDebug() << socket->readAll().data();
//    return;


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
