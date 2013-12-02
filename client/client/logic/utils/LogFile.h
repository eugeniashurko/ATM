#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

void createLog();

void openLog();

void closeLog();

void writeLog(const string& line);

void writeLog(const string& card, const string& date, const string& action,
			  const string& sum, const string& state);
