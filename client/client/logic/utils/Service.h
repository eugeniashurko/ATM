#include <iostream>
#include <string.h>
using namespace std;

bool isNum(const string& smth); //�������� �� � ����� ������
ostream& operator<<(ostream& os, const string& smth); //���� ����� �� �����
//�������� ��������� �����
bool operator==(const string& first, const string& second);
bool operator!=(const string& first, const string& second);
bool operator<(const string& first, const string& second);
bool operator<=(const string& first, const string& second);
bool operator>(const string& first, const string& second);
bool operator>=(const string& first, const string& second);
//����������� �������� ��� ������ ����
string allowedMoney(const string& balance, const string& frozen);
