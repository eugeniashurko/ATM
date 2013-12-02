#include "account.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>


Account::Account(const std::string& card,
        const std::string& pin,
        const std::string& name,
        const double available,
        const double hold) :
    _card_number(card),
    _name(name),
    _available(available),
    _hold(hold),
    _supplem_account(0)
{
    // Here we generate salt, use it for hasing the pin
    // and save salt and hashed pin in respective fields
    _salt = HashUtils::generateSalt();
    _pin_hash = HashUtils::generateHash(pin, _salt);
}
