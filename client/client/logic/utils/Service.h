#include <iostream>
#include <string.h>
using namespace std;

bool isNum(const string& smth); //перевірка чи є рядок числом
ostream& operator<<(ostream& os, const string& smth); //вивід рядка на екран
//операції порівняння рядків
bool operator==(const string& first, const string& second);
bool operator!=(const string& first, const string& second);
bool operator<(const string& first, const string& second);
bool operator<=(const string& first, const string& second);
bool operator>(const string& first, const string& second);
bool operator>=(const string& first, const string& second);
//вирахування доступної для зняття суми
string allowedMoney(const string& balance, const string& frozen);
