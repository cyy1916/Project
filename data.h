#pragma once
#include <string>
#include <vector>
#include "exception1.h"
using namespace std;
class Data
{
private:
	string str;
	long l;
	double d;
	vector<string> params;
	vector<string> innerDef;
	string fun;
	string funname;
public:
	Data();
	Data(long l);
	Data(string str);
	Data(double d);
	Data(long l, double d);
	Data(string funname, vector<string> params, string fun);
	Data(string funname, vector<string> params, vector<string> innerDef, string fun);
	long showLong();
	double showdouble();
	string showString();
	string show();
	string showFun();
	string showFunName();
	vector<string> showParams();
	vector<string> showInnerDef();
	bool judgeType(const char* type);
	bool isDefine();
	bool isLambda();
	bool isIf();
	bool isCond();
	bool isLet();
	bool isSetq();
	bool isLong();
	bool isDouble();
	bool isNum();
	bool isString();
	bool isJudgement();
	bool isEmpty();
	bool isFun();
	Data caculate(Data a, Data b);
	Data judgement(Data a, Data b);
	Data operator == (const Data & data);
	Data operator > (Data & data);
	Data operator < (Data & data);
	Data operator >= (Data & data);
	Data operator <= (Data & data);
	bool If();	
	void toString();
};

Data::Data()
{
	this->l = 0;
	this->str = "";
	this->d = 0;
	this->fun = "";
}

Data::Data(long l)
{
	this->l = l;
	this->str = "";
	this->d = 0;
	this->fun = "";
}

Data::Data(string str)
{
	this->str = str;
	this->l = 0;
	this->d = 0;
	this->fun = "";
}

Data::Data(double d)
{
	this->d = d;
	this->l = 0;
	this->str = "";
	this->fun = "";
}

Data::Data(long l, double d)
{
	this->d = d;
	this->l = l;
	this->str = "";
	this->fun = "";
}


Data::Data(string funname, vector<string> params, string fun)
{
	this->d = 0;
	this->l = 0;
	this->str = "";
	this->params = params;
	this->fun = fun;
	this->funname = funname;
}

Data::Data(string funname, vector<string> params, vector<string> innerDef, string fun)
{
	this->d = 0;
	this->l = 0;
	this->str = "";
	this->params = params;
	this->fun = fun;
	this->innerDef = innerDef;
	this->funname = funname;
}

bool Data::isLong()
{
	return (l != 0);
}

bool Data::isDouble()
{
	return (d != 0);
}

bool Data::isNum()
{
	return (!isString());
}

bool Data::isEmpty()
{
	if (!isLong() && !isDouble() && !isString() && params.size() == 0 && fun == "")
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Data::isString()
{
	return (str != "");
}

bool Data::isFun()
{
	return (fun != "");
}

long Data::showLong()
{
	return l;
}

double Data::showdouble()
{
	return d;
}

string Data::showString()
{
	string be = str.substr(0, 1);
	string end = str.substr(str.length() - 1, str.length());
	if (be == "\"" && end == "\"")
	{
		return str.substr(1, str.length() - 2);
	}
	else
	{
		return str.substr(0, str.length());
	}
	
}

string Data::show()
{
	return str;
}

string Data::showFunName()
{
	return funname;
}

string Data::showFun()
{
	return fun;
}

vector<string> Data::showParams()
{
	return params;
}

vector<string> Data::showInnerDef()
{
	return innerDef;
}

bool Data::judgeType(const char* type)
{
	if (type == str)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Data::isDefine()
{
	return judgeType("define");
}

bool Data::isLambda()
{
	return judgeType("lambda");
}

bool Data::isIf()
{
	return judgeType("if");
}

bool Data::isCond()
{
	return judgeType("cond");
}

bool Data::isLet()
{
	return judgeType("let");
}
bool Data::isSetq()
{
	return judgeType("set!");
}

bool Data::isJudgement()
{
	if (l == 1 && d == 1)
	{
		return true;
	}
	else if (l == -1 && d == -1)
	{
		return true;
	}
	return false;
}

Data Data::caculate(Data a, Data b)
{
	if (a.isNum() && b.isNum())
	{
		if (a.isLong() && b.isLong())
		{
			if (str == "+")
			{
				return Data(a.showLong() + b.showLong());
			}
			else if (str == "-")
			{
				return Data(a.showLong() - b.showLong());
			}
			else if (str == "*")
			{
				return Data(a.showLong() * b.showLong());
			}
			else if (str == "/")
			{
				return Data(a.showLong() /b.showLong());
			}
			else if (str == "==")
			{
				return a == b;
			}
		}
		else
		{
			if (str == "+")
			{
				return Data(a.showLong() + a.showdouble() + b.showdouble() + b.showLong());
			}
			else if (str == "-")
			{
				return Data(a.showLong() + a.showdouble() - b.showdouble() - b.showLong());
			}
			else if (str == "*")
			{
				return Data((a.showLong() + a.showdouble()) * (b.showdouble() - b.showLong()));
			}
			else if (str == "/")
			{
				return Data((a.showLong() + a.showdouble()) / (b.showdouble() - b.showLong()));
			}
			else if (str == "==")
			{
				return a == b;
			}
		}
		throw InterpreteError(2);
	}
	else if ((a.isNum() && b.isString()) || (a.isString() && b.isNum()))
	{
		if (str == "*")
		{
			string data = "";
			if (a.isString())
			{
				for (int i = 0; i < b.showLong(); i++)
				{
					data = data.append(a.showString());
				}
			}
			else
			{
				for (int i = 1; i < a.showLong(); i++)
				{
					data = data.append(b.showString());
				}
			}
			return Data(data);
		}
		throw InterpreteError(2);
	}
	else if (b.isString() && a.isString())
	{
		if (str == "+")
		{
			return Data(a.showString().append(b.showString()));
		}
		else if (str == "==")
		{
			return a == b;
		}
	}
	else if (a.isEmpty() && b.isEmpty())
	{
		return a == b;
	}
	throw InterpreteError(2);
}

Data Data::judgement(Data a, Data b)
{
	if (str == "==")
	{
		return a == b;
	}
	else if (str == "&&")
	{
		if (a.If() && b.If())
		{
			return Data(1, 1);
		}
	}
	else if (str == "||")
	{
		if (a.If() || b.If())
		{
			return Data(1, 1);
		}
	}
	else if (str == "||")
	{
		if (a.If() || b.If())
		{
			return Data(1, 1);
		}
	}
	return Data(-1, -1);
}

Data Data::operator == (const Data & data)
{
	if (l == data.l && d == data.d && params == data.params && fun == data.fun && str == data.str)
	{
		return Data(1, 1);
	}
	else
	{
		return  Data(-1, -1);
	}
}

Data Data::operator <= (Data & data)
{
	if (isString() || data.isString())
	{
		throw InterpreteError(3);
	}
	else
	{
		if (isLong() && data.isLong())
		{
			if (l <= data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isLong() && data.isDouble())
		{
			if (l <= data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isDouble())
		{
			if (d <= data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isLong())
		{
			if (d <= data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
	}

}

Data Data::operator >= (Data & data)
{
	if (isString() || data.isString())
	{
		throw InterpreteError(3);
	}
	else
	{
		if (isLong() && data.isLong())
		{
			if (l >= data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isLong() && data.isDouble())
		{
			if (l >= data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isDouble())
		{
			if (d >= data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isLong())
		{
			if (d >= data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
	}
}

Data Data::operator < (Data & data)
{
	if (isString() || data.isString())
	{
		throw InterpreteError(3);
	}
	else
	{
		if (isLong() && data.isLong())
		{
			if (l < data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isLong() && data.isDouble())
		{
			if (l < data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isDouble())
		{
			if (d > data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isLong())
		{
			if (d > data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
	}
}

Data Data::operator > (Data & data)
{
	if (isString() || data.isString())
	{
		throw InterpreteError(3);
	}
	else
	{
		if (isLong() && data.isLong())
		{
			if (l > data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isLong() && data.isDouble())
		{
			if (l > data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isDouble())
		{
			if (d > data.showdouble())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
		else if (isDouble() && data.isLong())
		{
			if (d > data.showLong())
			{
				return Data(1, 1);
			}
			else
			{
				return Data(-1, -1);
			}
		}
	}
}

bool Data::If()
{
	if (l == 1 && d == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Data::toString()
{
	if (isLong() && !isDouble())
	{
		cout << l << endl;
	}
	else if(!isLong() && isDouble())
	{
		cout << d << endl;
	}
	else if (isString())
	{
		cout << str << endl;
	}
	else if (isFun())
	{
		cout << "Fun { " << funname << "( ";
		for (int i = 0; i < params.size(); i++)
		{
			cout << params[i] << " ";
		}
		if (innerDef.size() != 0)
		{
			cout << " )( ";
			for (int i = 0; i < innerDef.size(); i++)
			{
				cout << innerDef[i] << " ";
			}
		}
		cout << " )( " << fun << " )" << endl;
	}
	else if (l == 1 && d == 1)
	{
		cout << "true" << endl;
	}
	else if (l == -1 && d == -1)
	{
		cout << "false" << endl;
	}
}
