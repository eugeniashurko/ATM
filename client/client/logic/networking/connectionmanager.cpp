#include "connectionmanager.h"

#include <QFile>
#include <QSslConfiguration>
#include <QUrl>
#include <QSslKey>
#include <QSslError>
#include <QSslSocket>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QEventLoop>
#include <QHttpPart>


const QString ConnectionManager::HOST = "37.139.13.175";
const QString ConnectionManager::PORT = "4443";

const QString ConnectionManager::GREET_URL = "/api";
const QString ConnectionManager::AUTH_URL = "/api/auth";
const QString ConnectionManager::BALANCE_URL = "/api/balance";
const QString ConnectionManager::WITHRAW_URL = "/api/withdraw";
const QString ConnectionManager::TRANSFER_URL = "/api/transfer";
const QString ConnectionManager::PERIODIC_URL = "/api/periodic";
const QString ConnectionManager::OVERFLOW_URL = "/api/overflow";
const QString ConnectionManager::NAME_URL = "/api/name";


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

    // .. but we decided not to do this for now to provide better security

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

       // request initialization
       QNetworkRequest * req = new QNetworkRequest();
       req->setSslConfiguration(*config);
       QUrl * u = new QUrl("https://" + HOST + ":" + PORT + AUTH_URL);
       req->setUrl(*u);
       req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

       // form the body of http request
       QVariant card_number(card), pin(PIN);
       QJsonObject json;
       json.insert("card", card_number.toString());
       json.insert("pin", pin.toString());
       QJsonDocument doc(json);

       QNetworkReply* reply = manager->post(*req, doc.toJson());

       // here we wait until reply is finished
       QEventLoop loop;
       connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
       connect(manager,
               SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
               reply,
               SLOT(ignoreSslErrors()));
       loop.exec();
       // processing the reply
       int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
       if (statusCode == 200) {
           // Reply of success so we
           // parse the JSON RespstatusCodeonse here to take token
           QByteArray reply_body = reply->readAll();
           QJsonParseError * err = new QJsonParseError;
           QJsonDocument doc = QJsonDocument::fromJson(reply_body, err);

           if (err->error != 0) {
               qDebug() << err->errorString();
           }

           if (doc.isNull()) {
               qDebug() << "Invalid JSON-document 'config.json'";
           } else if (doc.isObject()) {
               QVariantMap result = doc.toVariant().toMap();
               token = result["token"].toString();
           }
           delete err;

       }
       else if (statusCode == 401) {

           // if no such account in database
           throw AuthFailed();

       }
       else {

           qDebug() << statusCode;
           throw BadConnection();

       }

       delete reply;
       delete u;
       delete req;

    }
   return token;
}



const std::list<int> ConnectionManager::balanceRequest(QString token) {
    int available = 0;
    int hold = 0;
    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + BALANCE_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply* reply = manager->get(*req);

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 200) {
                // Reply of success so we
                // parse the JSON RespstatusCodeonse here to take token
                QByteArray reply_body = reply->readAll();
                QJsonParseError * err = new QJsonParseError;
                QJsonDocument doc = QJsonDocument::fromJson(reply_body, err);

                if (err->error != 0) {
                    qDebug() << err->errorString();
                }

                if (doc.isNull()) {
                    qDebug() << "Invalid JSON-document 'config.json'";
                } else if (doc.isObject()) {
                    QVariantMap result = doc.toVariant().toMap();
                    available = result["available"].toInt();
                    hold = result["hold"].toInt();
                }
                delete err;

            } else if (statusCode == 401) {

                qDebug() << "Token expired";
                throw TokenExpired();

            } else {

                qDebug() << statusCode;
                throw BadConnection();

            }
        delete reply;
        delete u;
        delete req;
    }
    std::list<int> list;
    list.push_back(available);
    list.push_back(hold);
    return list;
}



bool ConnectionManager::withdrawalRequest(const QString& token, const double sum) {

    bool success = false;

    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + WITHRAW_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        // form the body of http request
        QVariant amount(sum);
        QJsonObject json;
        json.insert("amount", amount.toString());
        QJsonDocument doc(json);

        QNetworkReply * reply = manager->post(*req, doc.toJson());

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        // - if successful and sufficient
        if (statusCode == 200) {

                success = true;
            // - if Unauthorized - token expired
            } else if (statusCode == 401) {

                qDebug() << "Token expired";
                throw TokenExpired();
            // - if Forbidden - insufficient funds
            } else if (statusCode == 403) { ; }
            // - some other connection errors
            else  {
                qDebug() << statusCode;
                throw BadConnection();
            }
        delete reply;
        delete u;
        delete req;
    }
    return success;
}


const QString ConnectionManager::nameRequest(const QString& token, const QString& card) {
    QString name="";
    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + NAME_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        q.addQueryItem("card", card);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply * reply = manager->get(*req);

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (statusCode == 200) {
            // Reply of success so we
            // parse the JSON RespstatusCodeonse here to take token
            QByteArray reply_body = reply->readAll();
            QJsonParseError * err = new QJsonParseError;
            QJsonDocument doc = QJsonDocument::fromJson(reply_body, err);

            if (err->error != 0) {
                qDebug() << err->errorString();
            }

            if (doc.isNull()) {
                qDebug() << "Invalid JSON-document 'config.json'";
            } else if (doc.isObject()) {
                QVariantMap result = doc.toVariant().toMap();
                name = result["name"].toString();
            }
            delete err;


            // - if Unauthorized - token expired
            } else if (statusCode == 400){

                qDebug() << "Card does not exist";
                throw NotExist();

            } else if (statusCode == 401) {

                qDebug() << "Token expired";
                throw TokenExpired();
            // - if Forbidden - insufficient funds
            } else if (statusCode == 403) { ; }
            // - some other connection errors
            else  {

                qDebug() << statusCode;
                throw BadConnection();

            }
        delete reply;
        delete u;
        delete req;
    }
    return name;
}

bool ConnectionManager::transferRequest(const QString& token, const QString& rec_card, const QString& sum) {
    bool success = false;

    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + TRANSFER_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // form the body of http request
        QVariant card(rec_card), vsum(sum);
        QJsonObject json;
        json.insert("amount", vsum.toDouble());
        json.insert("recepient", card.toString());
        QJsonDocument doc(json);

        QNetworkReply * reply = manager->post(*req, doc.toJson());

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (statusCode == 200) {
            success = true;
            // - if Unauthorized - token expired
            } else if (statusCode == 401) {

                qDebug() << "Token expired";
                throw TokenExpired();

            // - if Forbidden - insufficient funds
            } else if (statusCode == 403) {
            // - some other connection errors
                qDebug() << statusCode;
             }
            else  {

                qDebug() << statusCode;
                throw BadConnection();

            }
        delete reply;
        delete u;
        delete req;
    }
    return success;
}


bool ConnectionManager::setOverflow(const QString& token, const QString& sum, const QString& suppl) {
    bool success = false;

    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + OVERFLOW_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // form the body of http request
        QVariant card(suppl), vsum(sum);
        QJsonObject json;
        json.insert("recepient", card.toString());
        json.insert("threshold", vsum.toDouble());
        QJsonDocument doc(json);

        QNetworkReply * reply = manager->post(*req, doc.toJson());

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (statusCode == 200) {
            success = true;
            // - if Unauthorized - token expired
            } else if (statusCode == 401) {

                qDebug() << "Token expired";
                throw TokenExpired();

            // - if Forbidden - insufficient funds
            } else if (statusCode == 403) {
                qDebug() << statusCode;
                throw OverflowFailure();
            }
            else if (statusCode == 400) {
                qDebug() << statusCode;
                throw OverflowFailure();
            }
            // - some other connection errors
            else  {

                qDebug() << statusCode;
                throw BadConnection();

            }
        delete reply;
        delete u;
        delete req;
    }
    return success;
}


std::pair<QString, QString> ConnectionManager::getOverflow(const QString& token) {
    QString max_sum = "";
    QString suppl = "";
    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + OVERFLOW_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply* reply = manager->get(*req);

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 200) {
                // Reply of success so we
                // parse the JSON RespstatusCodeonse here to take token
                QByteArray reply_body = reply->readAll();
                QJsonParseError * err = new QJsonParseError;
                QJsonDocument doc = QJsonDocument::fromJson(reply_body, err);

                if (err->error != 0) {
                    qDebug() << err->errorString();
                }

                if (doc.isNull()) {
                    qDebug() << "Invalid JSON-document 'config.json'";
                } else if (doc.isObject()) {
                    QVariantMap result = doc.toVariant().toMap();
                    max_sum = result["threshold"].toString();
                    suppl = result["recepient"].toString();
                }
                delete err;

            } else if (statusCode == 401) {

                qDebug() << "Token expired";
                throw TokenExpired();

            } else {

                qDebug() << statusCode;
                throw BadConnection();

            }
        delete reply;
        delete u;
        delete req;
    }
    std::pair<QString, QString> res;
    res.first = max_sum;
    res.second = suppl;
    return res;
}


bool ConnectionManager::cleanOverflow(const QString& token) {
    bool success = false;

    if (manager->networkAccessible()) {
        // request initialization
        QNetworkRequest * req = new QNetworkRequest();
        req->setSslConfiguration(*config);
        // - we set url to have token as query
        QUrl * u = new QUrl("https://" + HOST + ":" + PORT + OVERFLOW_URL);
        QUrlQuery q;
        q.addQueryItem("token", token);
        u->setQuery(q);
        req->setUrl(*u);
        req->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply * reply = manager->deleteResource(*req);

        // here we wait until reply is finished
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        connect(manager,
                SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
                reply,
                SLOT(ignoreSslErrors()));
        loop.exec();
        // processing the reply
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (statusCode == 200) {
            success = true;
            // - if Unauthorized - token expired
            } else if (statusCode == 401) {

                throw TokenExpired();

            // - if Forbidden - insufficient funds
            } else if (statusCode == 403) { ; }
            // - some other connection errors
            else  {

                qDebug() << statusCode;
                throw BadConnection();

            }
        delete reply;
        delete u;
        delete req;
    }
    return success;
}
