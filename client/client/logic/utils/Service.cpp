#include "Service.h"
#include <sstream>
#include <stdlib.h>

bool isNum(const string& smth)
{
	bool check = true;
    const char * c = smth.c_str();
	for (size_t i = 0; i<smth.length(); i++)
	{
		if (c[i]<'0' || c[i]>'9')
		{
			check = false;
			break;
		}
	}
	return check;
};

ostream& operator<<(ostream& os, const string& smth)
{
	const char * csmth = smth.c_str();
	os<<csmth;
	return os;
}
bool operator==(const string& first, const string& second)
{
    bool equal = (first.length()==second.length());
	if(equal)
	{
		const char * f = first.c_str();
		const char * s = second.c_str();
		for (size_t i = 0; i<first.length(); i++)
		{
			if (f[i]!=s[i])
			{
				equal = false;
				break;
			}
		}
	}
	return equal;
};

bool operator!=(const string& first, const string& second)
{
	return !(first==second);
};

bool operator<(const string& first, const string& second)
{
	//якщо довжина менша або рівна та рядки не однакові
	bool equal = ((first.length()<=second.length()) && (first!=second));
	if(equal)
	{
		const char * f = first.c_str();
		const char * s = second.c_str();
		for (size_t i = 0; i<first.length(); i++)
		{
			if (f[i]>s[i])
			{
				equal = false;
				break;
			}
		}
	}
	return equal;
};

bool operator<=(const string& first, const string& second)
{
	if(first==second)
		return true;
	return first<second;
};

bool operator>(const string& first, const string& second)
{
	bool equal = ((first.length()>=second.length()) && (first!=second));
	if(equal)
	{
		const char * f = first.c_str();
		const char * s = second.c_str();
		for (size_t i = 0; i<first.length(); i++)
		{
			if (f[i]<s[i])
			{
				equal = false;
				break;
			}
		}
	}
	return equal;
};

bool operator>=(const string& first, const string& second)
{
	if(first==second)
		return true;
	return first>second;
};
string allowedMoney(const string& balance, const string& frozen)
{
    unsigned int ibalance = atoi(balance.c_str());
	unsigned int ifrozen = atoi(frozen.c_str());
	int allowed = ibalance - ifrozen;
    string s_allow = "0";
    if (allowed<0)
		cout<<"Insufficient funds in the account\n";
	else
	{
		stringstream convert;
		convert<<allowed;
		string s_allow = convert.str();
	}
	return s_allow;
}
