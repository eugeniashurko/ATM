#include "Validate.h"
#include "Service.h"

bool validPin(string& pin) //user's pin 4 numbers [0-9]
{
	if (pin.length()!=4)
		return false;
	else
		return isNum(pin);
};

bool validLog(string& login) //card number 16 number [0-9]
{
	if (login.length()!=16)
		return false;
	else
		return isNum(login);
};

bool validData(string& data); //data isn't past
bool validCash(const string& cash, const string& balance, const string& frozen) //for withdraw operations
{	
    if(!isNum(cash))
		return false;
	bool valid = true;
    string allow = allowedMoney(balance, frozen);
    if ((cash>allow) || (allow == "0"))
		valid = false;
	else valid = true;
	return valid;
};

bool validToken(const string& token);
