#include "connectionmanager.h"

#include <QFile>
#include <QSslConfiguration>
#include <QUrl>
#include <QSslKey>
#include <QSslError>
#include <QSslSocket>
#include <qjson/parser.h>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QEventLoop>
#include <QHttpPart>

// host address and port
const QString ConnectionManager::HOST = "37.139.13.175";
const QString ConnectionManager::PORT = "4443";

// urls defined in API
const QString ConnectionManager::GREET_URL = "/api";
const QString ConnectionManager::AUTH_URL = "/api/auth";
const QString ConnectionManager::BALANCE_URL = "/api/balance";
const QString ConnectionManager::WITHRAW_URL = "/api/withdraw";
const QString ConnectionManager::TRANSFER_URL = "/api/transfer";
const QString ConnectionManager::PERIODIC_URL = "/api/periodic";
const QString ConnectionManager::OVERFLOW_URL = "/api/overflow";


ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    config(new QSslConfiguration)
{
    // Here I open config-file and read host-address and port:

    //    QFile conf_file("ssl/config.json");
    //    if( ! conf_file.open( QIODevice::ReadOnly ))
    //    {
    //        qDebug() << "Cannot open configs!";
    //        return;
    //    }

    //    QByteArray json = conf_file.readAll();
    //    conf_file.close();

    //    QJsonParseError * err = new QJsonParseError;
    //    QJsonDocument doc = QJsonDocument::fromJson(json, err);

    //    if (err->error != 0) {
    //        qDebug() << err->errorString();
    //    }

    //    if (doc.isNull()) {
    //        qDebug() << "Invalid JSON-document 'config.json'";
    //    } else if (doc.isObject()) {
    //        QJsonObject jObject = doc.object();
    //        QVariantMap result = doc.toVariant().toMap();
    //        QString host = result["host"].toString();
    //        QString port = result["port"].toString();
    //    }

    // .. but we decided not to do this to provide better security

    QFile file( "ssl/client.key" );
    if( ! file.open( QIODevice::ReadOnly ) )
    {
        return;
    }
    QSslKey key(&file, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "password");
    config->setPrivateKey(key);
    file.close();

    QFile file1( "ssl/client.crt" );
    if( ! file1.open( QIODevice::ReadOnly ) )
    {
        return;
    }
    QList<QSslCertificate> sslCertificateList = QSslCertificate::fromData(file1.readAll(), QSsl::Pem);

    QSslCertificate sslCertificate = sslCertificateList.takeAt(0);
    config->setLocalCertificate(sslCertificate);
    file1.close();
 }


ConnectionManager::~ConnectionManager() {
    delete manager;
    manager = 0;

    delete config;
    config = 0;
}

// Function for checking the connection
bool ConnectionManager::checkConnection() {
    bool ok = false;
    // 1) Check the connection to network
    if (manager->networkAccessible()) {
        // 2) Check whether the greeting to server is successful
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + GREET_URL);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "*");
        QNetworkReply* reply = manager->get(*req);

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();


        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (reply->error() == QNetworkReply::NoError) {
            if (statusCode == 200) {
                ok = true;
            } else {
                qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            }
        } else {
            qDebug() << reply->errorString();
        }
        delete reply;
        delete u;
        delete req;
    } else {
        qDebug() << "Network is not accessible";
    }
    return ok;
}

QString ConnectionManager::authRequest(QString card, QString PIN) {
    QString token = "";
    if (manager->networkAccessible()) {

       QNetworkRequest * req = new QNetworkRequest();
       req->setSslConfiguration(*config);
       QUrl * u = new QUrl("https://" + HOST + ":" + PORT + AUTH_URL);
       req->setUrl(*u);
       req->setHeader(QNetworkRequest::ContentTypeHeader, "appication/json");

       // form the body of http request
       QString request_body(
                             "{"
                                 "\"card\" : " + card + ","
                                 "\"pin\" : " + PIN +
                             "}"
                           );

       QNetworkReply* reply = manager->post(*req, request_body.toStdString().c_str());
       QEventLoop loop;
       connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
       connect(manager,
               SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
               reply,
               SLOT(ignoreSslErrors()));
       loop.exec();

       int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
       if ((statusCode == 200) && (reply->error() == QNetworkReply::NoError)) {
           // Parse the JSON Response here
           QByteArray reply_body = reply->readAll();
           QJsonParseError * err = new QJsonParseError;
           QJsonDocument doc = QJsonDocument::fromJson(reply_body, err);

           if (err->error != 0) {
               qDebug() << err->errorString();
           }

           if (doc.isNull()) {
               qDebug() << "Invalid JSON-document 'config.json'";
           } else if (doc.isObject()) {
               QJsonObject jObject = doc.object();
               QVariantMap result = doc.toVariant().toMap();
               token = result["token"].toString();
           }
       }
       else {
           qDebug() << reply->errorString();
           qDebug() << statusCode;
           throw BadConnection();
       }
       delete reply;
       delete u;
       delete req;
   }
   return token;
}

const int ConnectionManager::balanceRequest(QString token) {
    bool ok = false;
    if (manager->networkAccessible()) {
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + BALANCE_URL);
        // session token in query
        QUrlQuery query;
        query.addQueryItem("token", token);
        u->setQuery(query.query());
        req->setUrl(*u);
        QNetworkReply* reply = manager->get(*req);
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if ((statusCode == 200) && (reply->error() == QNetworkReply::NoError)) {
            ok = true;
        } else if (statusCode == 401) {
            throw TokenExpired();
        }
        else {
            qDebug() << reply->errorString();
            qDebug() << statusCode;
            throw BadConnection();
        }
        delete reply;
        delete u;
        delete req;
    }
    return ok;
}

//void ConnectionManager::withdrawalRequest(QString card, int sum) {
//    QNetworkRequest request;
//    request.setUrl(WITHDRAW_URL);
//    QNetworkReply *reply = manager ->get(request);
//}
