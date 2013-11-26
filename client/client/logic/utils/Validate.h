#include <iostream>
#include <string.h>
using namespace std;

bool validPin(string& pin); //user's pin 4 numbers [0-9]

bool validLog(string& login); //card number 16 number [0-9]

bool validData(string& data); //data isn't past

bool validCash(const string& cash, const string& balance, const string& frozen); //for withdraw operations

bool validToken(const string& token);
