#ifndef TELLER_H
#define TELLER_H

#include "banknotecombination.h"

#include <string>

class Teller
{
public:
    Teller(const QString& file_name);
    ~Teller() {}

    class InvalidSumException {
    private:
        std::string reason;
    public:
        InvalidSumException(std::string s="Invalid Sum!"): reason(s) {}
        ~InvalidSumException() {}
    };


    const BanknoteCombination& withdraw(const int sum);
    const BanknoteCombination& getCombo() { return combo; }

private:
    BanknoteCombination combo;
};

#endif // TELLER_H
