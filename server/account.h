#ifndef ACCOUNT_H
#define ACCOUNT_H

#endif // ACCOUNT_H

#include <QString>

using namespace std;

class Account {

private:
    QString _card_number;
    QString _PIN;
    QString _name;
    QString _surname;
    int _balance;
    int _blockedSum;
    int _maxBalance;

public:
    Account(QString cardNumber, QString PIN, QString name, QString surname,
            int balance=0, int blockedSum=0, int maxBalance=0);
    ~Account();

    QString cardNumber() { return _card_number; }
    QString PIN() { return _PIN; }
    QString name() { return _name; }
    QString surname() { return _surname; }

    int balance() { return _balance; }
    int blockedSum() { return _blockedSum; }
    int maxBalance() { return _maxBalance; }

};
