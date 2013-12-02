#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "hashutils.h"

class Account;

class Account
{
private:
    Account() {}

    // it will be our primary key
    std::string _card_number;

    std::string _salt;
    std::string _pin_hash;
    std::string _name;

    double _available;
    double _hold;
    double _max_sum;

    // we don't control the lifetime of this object
    // we can share it with others
    const Account * _supplem_account;

public:
    Account(const std::string& card,
            const std::string& pin,
            const std::string& name,
            const double available=0,
            const double hold=0);
    ~Account() {}

    const std::string& cardNumber() const { return _card_number; }
    const std::string& salt() const { return _salt; }
    const std::string& pinHash() const { return _pin_hash; }
    const std::string& name() const { return _name; }
    const double available() const { return _available; }
    const double hold() const { return _hold; }
    const double maxSum() const { return _max_sum; }
    const Account * supplemAccount() const { return _supplem_account; }

    void setSalt(const std::string& s) { _salt = s; }
    void setPinHash(const std::string& h) { _pin_hash = h; }
    void setName(const std::string& n) { _name = n; }
    void setAvailable(const double a) { _available = a; }
    void setHold(const double h) { _hold = h; }
    void setMaxSum(const double m) { _max_sum = m; }
    void setSupplemAccount(const Account * a) { _supplem_account = a; }
};

#endif // ACCOUNT_H
