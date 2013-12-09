#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonObject>
#include <iostream>
#include "teller.h"

using namespace std;

typedef pair<unsigned int, unsigned int> banknote;

Teller::Teller(const QString& file_name): combo(0, 0, 0, 0, 0, 0) {
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
        combo = BanknoteCombination(result["10"].toInt(), result["20"].toInt(), result["50"].toInt(), result["100"].toInt(),
                result["200"].toInt(), result["500"].toInt());
    }
    return;
}


bool check (unsigned int smth)
    { return (smth % 10 == 0); }


const BanknoteCombination& Teller::withdraw(const int sum) {
    BanknoteCombination cash_to_go(0, 0, 0, 0, 0, 0);

    int withdraw = sum;

    int n10  = 0;
    int n20 = 0;
    int n50 = 0;
    int n100 = 0;
    int n200 = 0;
    int n500 = 0;

    int here10  = combo.get10();
    int here20 = combo.get20();
    int here50 = combo.get50();
    int here100 = combo.get100();
    int here200 = combo.get200();
    int here500 = combo.get500();

    while ((withdraw >= 500) && (here500 > 0)) {
        n500++;
        here500--;
        withdraw -= 500;
    }
    while ((withdraw >= 200) && (here200 > 0)) {
        n200++;
        here200--;
        withdraw -= 200;
    }
    while ((withdraw >= 100) && (here100 > 0)) {
        n100++;
        here100--;
        withdraw -= 100;
    }
    while ((withdraw >= 50) && (here50 > 0)) {
        n50++;
        here50--;
        withdraw -= 50;
    }
    while ((withdraw >= 20) && (here20 > 0)) {
        n20++;
        here20--;
        withdraw -= 20;
    }
    while ((withdraw >= 10) && (here10 > 0)) {
        n10++;
        here10--;
        withdraw -= 10;
    }

    qDebug() << "Form the sum:";
    qDebug() << n10;
    qDebug() << n20;
    qDebug() << n50;
    qDebug() << n100;
    qDebug() << n200;
    qDebug() << n500;


    if (withdraw != 0) {
        throw InvalidSumException("Sum is invalid");
    } else {
        combo.set10(here10);
        combo.set20(here20);
        combo.set50(here50);
        combo.set100(here100);
        combo.set200(here200);
        combo.set500(here500);
        qDebug() << "Combo left:";
        qDebug() << combo.get10();
        qDebug() << combo.get20();
        qDebug() << combo.get50();
        qDebug() << combo.get100();
        qDebug() << combo.get200();
        qDebug() << combo.get500();

        cash_to_go.set10(n10);
        cash_to_go.set20(n20);
        cash_to_go.set50(n50);
        cash_to_go.set100(n100);
        cash_to_go.set200(n200);
        cash_to_go.set500(n500);
    }
    return cash_to_go;
}


