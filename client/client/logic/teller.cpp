#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>

#include "teller.h"


Teller::Teller(const QString& file_name) {
    QFile conf_file(file_name.toStdString().c_str());
    if( ! conf_file.open( QIODevice::ReadOnly ))
    {
        qDebug() << "Cannot open configs!";
        return;
    }

    QByteArray json = conf_file.readAll();
    conf_file.close();

    QJsonParseError * err = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(json, err);

    if (err->error != 0) {
        qDebug() << err->errorString();
    }

    if (doc.isNull()) {
        qDebug() << "Invalid JSON-document 'config.json'";
    } else if (doc.isObject()) {
        QJsonObject jObject = doc.object();
        QVariantMap result = doc.toVariant().toMap();
        _20 = result["20"].toInt();
        _50 = result["50"].toInt();
        _100 = result["100"].toInt();
        _200 = result["200"].toInt();
        _500 = result["500"].toInt();
    }
    return;
}
