#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "exception1.h"
using namespace std;

class Codereader
{
private:
	string ini;
	int leng;
	int index;
public:
	Codereader();
	Codereader(string str);
	Codereader(const Codereader & c);
	Node manage();
	int showlength();
	int showindex();
	int isstandard();
	friend int isstand(string ini);
};
Codereader::Codereader()
{
	leng = 0;
}

Codereader::Codereader(string str)
{
	leng = str.length();
	index = 0;
	ini = new char[leng + 1];
	ini = str;
}

Codereader::Codereader(const Codereader &other)
{
	leng = other.leng;
	index = other.index;
	ini = other.ini;
}

int isstand(string ini)
{
	int right = 0;
	int left = 0;
	for (int i = 0; i < ini.length(); i++)
	{
		if (ini[i] == ')')
		{
			right++;
		}
		else if (ini[i] == '(')
		{
			left++;
		}
	}
	if (right > left)
	{
		return 0;
	}
	else if(right == left)
	{
		if (right == 0)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 2;
	}
}
int Codereader::isstandard()
{
	int right = 0;
	int left = 0;
	for (int i = 0; i < ini.length(); i++)
	{
		if (ini[i] == ')')
		{
			right++;
		}
		else if (ini[i] == '(')
		{
			left++;
		}
	}
	if (right > left)
	{
		return 0;
	}
	else if (right == left)
	{
		if (right == 0)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 2;
	}
}
Node Codereader::manage()
{
	int left = 0;
	int right = 0;
	int j = 1;
	if (isstand(ini) == 0)
	{
		throw InterpreteError(1);
	}
	if (isstand(ini) == 2)
	{
		return Node();
	}
	else
	{
		while (index < leng)
		{
			if (ini[index] == ' ')
			{
				index++;
			}
			else if (ini[index] == '(' || ini[index] == ')')
			{
				index++;
				return Node(ini, index - 1, index);
			}
			else if (ini[index] == '"')
			{
				index++;
				int k = index;
				while (ini[index] != '"' && index <= leng)
				{
					index++;
				}
				index++;
				return Node(ini, k - 1, index);
			}
			else
			{
				int k = index;
				while (ini[index] != ' ' && index < leng && ini[index] != '(' && ini[index] != ')')
				{
					index++;
				}
				return Node(ini, k, index);
			}
		}
	}
	return Node();
}

int Codereader::showindex()
{
	return index;
}

int Codereader::showlength()
{
	return leng;
}
