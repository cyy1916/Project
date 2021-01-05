#pragma once
#include <string>
#include <string.h>
#include "enviroment.h"
using namespace std;
class Node
{
private:
	string node;
	int length;
	bool isstand = true;
public:
	Node();
	Node(const char* a);
	Node(string a);
	Node(bool isstand);
	Node(string str, int i, int j);
	Node(char* node, int i, int j);
	string show();
	void tostring();
	bool isLong();
	bool isDouble();
	long toLong();
	bool isOperator();
	bool isJudgement();
	double toDouble();
	bool isString();
	bool judgeType(const char* type);
	bool isDefine();
	bool isLambda();
	bool isIf();
	bool isCond();
	bool isLet();
	bool isSetq();
	bool isFun();
	bool toisstand();
	bool isempty();
};

Node::Node()
{
	length = 0;
}

Node::Node(const char* a)
{
	node = a;
	length = node.length();
}

Node::Node(string a)
{
	node = a;
	length = node.length();
}

Node::Node(string str, int i, int j)
{
	node = str.substr(i, j - i);
	length = j - i;
}


Node::Node(char* node, int i, int j)
{
	this->node = new char[j - i + 1];
	for (int p = i; p < j; p++)
	{
		this->node[p - i] = node[p];
	}
	length = j - i;
}

Node::Node(bool isstand)
{
	this->isstand = isstand;
}


string Node::show()
{
	return node;
}

void Node::tostring()
{
	cout << node;
}

bool Node::isString()
{
	for (int i = 0; i < length; i++)
	{
		if (node[i] == '"')
		{
			return true;
		}

	}
	return false;
}

bool Node::isOperator()
{
	if (length == 1)
	{
		if (node == "+" || node == "-" || node == "*" || node == "/")
		{
			return true;
		}
	}
	else if (length == 2)
	{
		if (node == "==" || node == ">=" || node == "<=" || node == ">" || node == "<")
		{
			return true;
		}
	}
	return false;
}

bool Node::isJudgement()
{
	if (length == 2)
	{
		if (node == "&&" || node == "||" )
		{
			return true;
		}
	}
	else if (length == 1)
	{
		if (node == ">" || node == "<")
		{
			return true;
		}
	}
	return false;
}

bool Node::isLong()
{
	for (int i = 0; i < length; i++)
	{
		if (node[i] < '0' || node[i] > '9')
		{
			return false;
		}
	}
	return true;
}

bool Node::isDouble()
{
	int k = 0;
	for (int i = 0; i < length; i++)
	{
		if ((node[i] < '0' || node[i] > '9') && (node[i] != '.'))
		{
			return false;
		}
		if (node[i] == '.')
		{
			k++;
		}
	}
	if (k == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

long Node::toLong()
{
	return atol(node.c_str());
}

double Node::toDouble()
{
	return atof(node.c_str());
}

bool Node::judgeType(const char* type)
{
	if (type == node)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::isDefine()
{
	return judgeType("define");
}

bool Node::isLambda()
{
	return judgeType("lambda");
}

bool Node::isIf()
{
	return judgeType("if");
}

bool Node::isCond()
{
	return judgeType("cond");
}

bool Node::isLet()
{
	return judgeType("let");
}
bool Node::isSetq()
{
	return judgeType("setq");
}

bool Node::isFun()
{
	return true;
}

bool Node::toisstand()
{
	return isstand;
}

bool Node::isempty()
{
	if (length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
