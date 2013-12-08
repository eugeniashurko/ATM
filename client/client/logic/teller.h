#ifndef TELLER_H
#define TELLER_H
#include "banknotecombination.h"

class Teller
{
public:
    Teller(const QString& file_name);
    ~Teller() {}

    class InvalidSumException {
    public:
        InvalidSumException() {}
        ~InvalidSumException() {}
    };


    const BanknoteCombination& withdraw(const int sum);

private:
    BanknoteCombination combo;
};

#endif // TELLER_H
