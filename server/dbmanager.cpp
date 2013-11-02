#include "dbmanager.h"


DBManager::DBManager(QObject *parent){
}

DBManager::~DBManager() {};

bool DBManager::openDB() {
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bank.db");

    // Open databasee
    return db.open();
}

bool DBManager::createAccountTable() {
    // Create table "account"
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("create table accounts"
                         "(card_number varchar(16) primary key, "
                         "PIN varchar(20),"
                         "firstname varchar(20), "
                         "lastname varchar(20), "
                         "balance integer,"
                         "blockedSum integer,"
                         "maxBalance integer);");

    }
    return ret;
}

bool DBManager::insertAccount(Account & a) {
    QSqlQuery query;
    QString str_insert = "INSERT INTO accounts"
                         "VALUES (%1, '%2', %3, %4, %5, %6, %7);";

    QString str = str_insert.arg(a.cardNumber())
                .arg(a.PIN())
                .arg(a.name())
                .arg(a.surname())
                .arg(a.balance())
                .arg(a.blockedSum())
                .arg(a.maxBalance());

    bool b = query.exec(str);

    return b;
}

QSqlError DBManager::lastError() {
    return db.lastError();
}
