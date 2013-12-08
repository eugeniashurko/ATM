#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <iostream>
#include "teller.h"

using namespace std;


Teller::Teller(const QString& file_name): combo(0, 0, 0, 0, 0) {
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
        combo = BanknoteCombination(result["20"].toInt(), result["50"].toInt(), result["100"].toInt(),
                result["200"].toInt(), result["500"].toInt());
    }
    return;
}

const BanknoteCombination& Teller::withdraw(const int sum) {
    // TODO code here
}
