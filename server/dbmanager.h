#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "account.h"

#include <QtSql>

class Account;
class DBManager
{
public:
    DBManager(QObject *parent=0);
    ~DBManager();

    bool openDB();
    bool createAccountTable();
    bool insertAccount(Account& a);
    QSqlError lastError();

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
