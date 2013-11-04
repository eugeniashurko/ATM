#include "account.h"

 #include <QCryptographicHash>

Account::Account(QString cardNumber,
                 QString PIN,
                 QString name,
                 QString surname,
                 int balance,
                 int blockedSum,
                 int maxBalance):
    _card_number(cardNumber), _name(name),
    _surname(surname), _balance(balance),
    _blockedSum(blockedSum), _maxBalance(maxBalance)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(PIN.toUtf8());
    this->_PIN = hash.result();
    return;
}

Account::~Account() {}
