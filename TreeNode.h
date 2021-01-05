#pragma once
#include "Node.h"
#include <deque>
#include "data.h"
#include "exception1.h"
#include "Codereader.h"
#include <vector>
#include <algorithm>
class TreeNode
{
private:
	Node val;
	vector<TreeNode> sons;
	environment envir;
public:
	TreeNode() {}
	TreeNode(Node val);
	TreeNode(const char* str);
	TreeNode(Node val, vector<TreeNode> son);
	Data execute(environment & env);
	Data executeIf(environment & env);
	Data executeCond(environment & env);
	Data executeSetq(environment  & env);
	Data executeLet(environment & env);
	Data executeDef(environment & env);
	Data executeLambda(environment & env);
	environment getSonEnvForLet(environment & env);
	Data caculate(Data op, Data a, Data b);
	Data Judgement(Data op, Data a, Data b);
	bool isDouble();
	bool isLong();
	bool isString();
	bool isOperator();
	bool isJudgement();
	bool isValue();
	bool isFun(environment & env);
	bool isDefine();
	bool isLambda();
	bool isIf();
	bool isCond();
	bool isLet();
	bool isSetq();
	bool isempty();
	bool isLambdaFun();
	string show();
	int getSonsSize();
	string getSonsFunc(string function);
	string getInnerFunc(string function, vector<string> params, environment env);
	TreeNode grabFather(TreeNode & father);
	TreeNode getSon(int index);
	TreeNode getTreeNode(string str);
	vector<TreeNode> getSons();
	vector<string>getDefParams();
	void setSons(vector<TreeNode> & sons);
	void addSon(TreeNode & son);
	void Tostring();
	bool isKey();
	string getOperator();
	environment toEnv();
};

TreeNode::TreeNode(Node val)
{
	this->val = val;
}

TreeNode::TreeNode(const char* str)
{
	val = Node(str);
}

TreeNode::TreeNode(Node val, vector<TreeNode> son)
{
	this->val = val;
	this->sons = son;
}

TreeNode TreeNode::getSon(int index)
{
	return sons.at(index);
}

vector<TreeNode> TreeNode::getSons()
{
	return sons;
}

bool TreeNode::isKey()
{
	if (isValue() && !(val.isDouble() || val.isLong()))
	{
		return true;
	}
	else if(sons.size() == 1 && !(sons.at(0).isDouble() || sons.at(0).isLong()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TreeNode::setSons(vector<TreeNode> & sons)
{
	this->sons.insert(this->sons.end(), sons.begin(), sons.end());
}

void TreeNode::addSon(TreeNode & son)
{
	sons.push_back(son);
}

string TreeNode::getOperator()
{
	return sons.at(sons.size() - 1).show();
}

int TreeNode::getSonsSize()
{
	return sons.size();
}

bool TreeNode::isLong()
{
	return val.isLong();
}

bool TreeNode::isDouble()
{
	return val.isDouble();
}

bool TreeNode::isString()
{
	return val.isString();
}

bool TreeNode::isOperator()
{
	return val.isOperator();
}

bool TreeNode::isJudgement()
{
	return val.isJudgement();
}

bool TreeNode::isDefine()
{
	return sons.at(sons.size() - 1).val.isDefine();
}

bool TreeNode::isLambda()
{
	if (sons.at(sons.size() - 1).sons.size() == 0)
	{
		return false;
	}
	else
	{
		return sons.at(sons.size() - 1).sons.at(sons.at(sons.size() - 1).sons.size() - 1).val.isLambda();
	}
}

bool TreeNode::isIf()
{
	return sons.at(sons.size() - 1).val.isIf();
}

bool TreeNode::isCond()
{
	return sons.at(sons.size() - 1).val.isCond();
}

bool TreeNode::isLet()
{
	return sons.at(sons.size() - 1).val.isLet();
}
bool TreeNode::isSetq()
{
	return sons.at(sons.size() - 1).val.isSetq();
}

bool TreeNode::isFun(environment & env)
{
	if (!env.search(val.show()).isEmpty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TreeNode::isValue()
{
	if (sons.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TreeNode::isempty()
{
	if (val.isempty() && sons.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TreeNode::isLambdaFun()
{
	return sons.at(0).execute(envir).isFun();
}

TreeNode TreeNode::getTreeNode(string str)
{
	Codereader input(str);
	deque<TreeNode> stack;
	TreeNode root;
	bool isstand = true;;
	root = TreeNode(input.manage());
	if (!root.isempty())
	{
		stack.push_front(root);
		while (input.showindex() < input.showlength())
		{
			Node val = input.manage();
			if (")" == val.show())
			{
				root = TreeNode(" ");
				TreeNode tmp = stack.front();
				stack.pop_front();
				while ("(" != tmp.show())
				{
					root = root.grabFather(tmp);
					tmp = stack.front();
					stack.pop_front();
				}
				stack.push_front(root);
			}
			else
			{
				stack.push_front(TreeNode(val));
			}
		}	
		isstand = true;
	}
	else
	{
		isstand = false;
	}
	return root;

}

environment TreeNode::toEnv()
{
	return envir;
}

vector<string> TreeNode::getDefParams()
{
	vector<string> params;
	int size = sons.size();
	for (int i = sons.at(sons.size() - 2).sons.size() - 2; i >= 0 ; i--)
	{
		TreeNode param = sons.at(sons.size() - 2).sons.at(i);
		if (!param.isKey()) {
			throw InterpreteError(14);
		}
		params.push_back(param.show());
	}
	return params;
}

string TreeNode::getSonsFunc(string function)
{
	if (" " == val.show())
	{
		function += "( ";
		function = sons.at(sons.size() - 1).getSonsFunc(function);
		for (int i = sons.size() - 2; i >= 0; i--)
		{
			function = sons.at(i).getSonsFunc(function);
			function += " ";
		}

		function += " )";
	}
	else
	{
		function += val.show();
		function += " ";
	}
	return function;
}
string TreeNode::getInnerFunc(string function, vector<string> params, environment env)
{
	if (" " == val.show())
	{
		function += "( ";
		function = sons.at(sons.size() - 1).getSonsFunc(function);
		for (int i = sons.size() - 2; i >= 0; i--)
		{
			function = sons.at(i).getSonsFunc(function);
			function += " ";
		}

		function += " )";
	}
	else
	{
		vector<string>::iterator result = find(params.begin(), params.end(), val.show());
		if (!env.search(val.show()).isEmpty() && result == params.end())
		{
			if (env.search(val.show()).isLong())
			{
				function += env.search(val.show()).showLong();
			}
			else if (env.search(val.show()).isDouble())
			{
				function += env.search(val.show()).showdouble();
			}
			else if (env.search(val.show()).isString())
			{
				function += env.search(val.show()).show();
			}
			else if (env.search(val.show()).isFun())
			{
				function += env.search(val.show()).showFun();
			}
		}
		else
		{
			function += val.show();
		}
		function += " ";
	}
	return function;
}

string TreeNode::show()
{
	return val.show();
}

TreeNode TreeNode::grabFather(TreeNode & son)
{
	sons.push_back(son);
	return *this;
}

void TreeNode::Tostring()
{
	if (" " == val.show())
	{
		cout << "( ";
		sons.at(sons.size() - 1).Tostring();
		for (int i = sons.size() - 2; i >= 0; i--)
		{
			sons.at(i).Tostring();
			cout << " ";
		}

		cout << " )";
	}
	else
	{
		val.tostring();
		cout << " ";
	}
}

Data TreeNode::executeIf(environment & env)
{
	if (sons.size() != 4)
	{
		throw InterpreteError(7);
	}
	if (sons.at(2).execute(env).If())
	{
		return sons.at(1).execute(env);
	}
	else 
	{
		return sons.at(0).execute(env);
	}
}

Data TreeNode::executeCond(environment & env)
{
	if (sons.size() == 1) 
	{
		throw InterpreteError(6);
	}
	env.put("else", Data(1, 1));
	vector<TreeNode> sonss = sons;
	for (int i = 1; i < sons.size(); i++) 
	{
		TreeNode son = sonss.at(i);
		if (son.sons.size() > 2) 
		{
			throw InterpreteError(6);
		}
		if (son.sons.size() == 2) 
		{
			if (son.sons.at(0).execute(env).If()) 
			{
				return son.getSon(1).execute(env);
			}
		}
		else 
		{
			return son.execute(env);
		}
	}
	throw InterpreteError(6);
}

Data TreeNode::executeDef(environment  & env)
{
	if (sons.size() < 3)
	{
		throw InterpreteError(4);
	}
	if (sons.at(1).isKey())
	{
		if (sons.size() != 3)
		{
			throw InterpreteError(4);
		}
		if (sons.at(1).sons.size() == 0)
		{
			
			if (!env.search(sons.at(1).show()).isEmpty())
			{
				env.erase(sons.at(1).show());
			}
			Data res = sons.at(0).execute(env);
			env.put(sons.at(1).show(), res);
			envir = env;
			return res;
		}
		else
		{
			Data res = sons.at(0).execute(env);
			env.put(sons.at(1).sons.at(0).show(), res);
			envir = env;
			return res;
		}
	}
	else if(sons.size() == 3)
	{
		string funName = sons.at(sons.size() - 2).getOperator();
		Data data(funName, getDefParams(), sons.at(0).getSonsFunc(""));
		env = env.put(funName, data);
		envir = env;
		return TreeNode(Node(funName)).execute(env);
	}
	else
	{
		string funName = sons.at(sons.size() - 2).getOperator();
		vector<string> innerDef;
		for (int i = sons.size() - 3; i > 0; i--)
		{
			innerDef.push_back(sons.at(i).getSonsFunc(""));
		}
		Data data(funName, getDefParams(), innerDef, sons.at(0).getSonsFunc(""));
		env = env.put(funName, data);
		envir = env;
		return TreeNode(Node(funName)).execute(env);
	}
}

Data TreeNode::executeSetq(environment & env)
{
	if (sons.size() != 3) 
	{
		throw InterpreteError(5);
	}
	if (!sons.at(1).isKey()) 
	{
		throw InterpreteError(5);
	}
	Data val = sons.at(0).execute(env);
	string key = sons.at(1).show();
	env.set(key, val);
	return val;
}

environment TreeNode::getSonEnvForLet(environment & env)
{
	vector<TreeNode> nodes = sons;
	environment sonEnv(env);
	for (TreeNode var : nodes)
	{
		TreeNode key = var.getSon(0);
		if (!key.isKey() || var.sons.size() != 2)
		{
			throw InterpreteError(8);
		}
		sonEnv.put(key.show(), var.getSon(1).execute(sonEnv));
	}
	return sonEnv;
}

Data TreeNode::executeLet (environment & env)
{
	if (sons.size() != 3) 
	{
		throw InterpreteError(9);
	}
	TreeNode res = sons.at(2);
	environment sonEnv = sons.at(1).getSonEnvForLet(env);
	return res.execute(sonEnv);
}

Data TreeNode::executeLambda(environment & env)
{
	vector<string> params;
	if (sons.at(sons.size() - 1).sons.at(1).isValue())
	{
		string param = sons.at(sons.size() - 1).sons.at(1).show();
		if (!(" " == param))
		{
			params.push_back(param);
		}
	}
	else {
		for (TreeNode param : sons.at(sons.size() - 1).sons.at(1).getSons()) 
		{
			params.push_back(param.show());
		}
	}
	TreeNode fun = sons.at(sons.size() - 1).sons.at(0);
	if (fun.isValue())
	{
		return env.search(fun.show());
	}
	else
	{
		environment envFun;
		for (int i = 0; i < params.size(); i++)
		{
			envFun.put(params.at(i), sons.at(i).execute(env));
		}
		envFun.setFather(env);
		return fun.execute(envFun);
	}
}

Data TreeNode::execute(environment & env)
{
	if (isDouble())
	{
		return Data(val.toDouble());
	}
	else if (isLong())
	{
		return Data(val.toLong());
	}
	else if (isString())
	{
		return Data(val.show());
	}
	else if (isValue())
	{
		if (" " == val.show())
		{
			return Data();
		}
		else if (env.search(val.show()).isEmpty())
		{
			if (isOperator() || isJudgement())
			{
				return Data(val.show());
			}
			else
			{
				throw InterpreteError(10);
			}
		}
		return env.search(val.show());
	}
	else
	{
		if (sons.size() == 1)
		{
			return sons[0].execute(env);
		}
		else if (isIf())
		{
			return executeIf(env);
		}
		else if (isCond())
		{
			return executeCond(env);
		}
		else if (isLambda())
		{
			return executeLambda(env);
		}
		else if (isLet())
		{
			return executeLet(env);
		}
		else if (isSetq())
		{
			return executeSetq(env);
		}
		else if (isDefine())
		{
			return executeDef(env);
		}
		else if(sons.at(sons.size() - 1).isFun(env))
		{
			Data function = env.search(sons.at(sons.size() - 1).show());
			if (sons.size() - 1 != function.showParams().size())
			{
				throw InterpreteError(11);
			}
			else
			{
				string func = function.showFun();
				TreeNode fun = getTreeNode(func);
				if (fun.isDouble() || fun.isLong() || fun.isString() || fun.isOperator() || fun.isJudgement())
				{ 
					return env.search(fun.show());
				}
				else
				{
					environment envFun;
					envFun.setFather(env);
					if (function.showInnerDef().size() == 0)
					{
						for (int i = 0; i < function.showParams().size(); i++)
						{
							envFun.put(function.showParams().at(i), sons.at(function.showParams().size() - 1 - i).execute(env));
						}
						if (fun.execute(envFun).isFun())
						{
							env.put(fun.execute(envFun).showFunName(), fun.execute(envFun));
						}
						return fun.execute(envFun);
					}
					else
					{
						for (int i = 0; i < function.showInnerDef().size(); i++)
						{
							TreeNode innerDef = getTreeNode(function.showInnerDef()[i]);
							innerDef.execute(envFun);
						}
						for (int i = 0; i < function.showParams().size(); i++)
						{
							envFun.put(function.showParams().at(i), sons.at(function.showParams().size() - 1 - i).execute(env));
						}
						if (fun.execute(envFun).isFun())
						{
							env.put(fun.execute(envFun).showFunName(), fun.execute(envFun));
						}
						return fun.execute(envFun);
					}
				}
			}
		}
		else if (sons.at(sons.size() - 1).execute(env).isFun())
		{
			TreeNode root = " ";
			for (int i = 0; i < sons.size() - 1; i++)
			{
				root.grabFather(sons.at(i));
			}
			TreeNode InnerDef = sons.at(sons.size() - 1);
			Data Def = InnerDef.execute(env);
			TreeNode tmp = getTreeNode(Def.showFunName());
			root.grabFather(tmp);
			return root.execute(env);
		}
		else if (sons.at(sons.size() - 1).isOperator())
		{
			Data data = sons.at(sons.size() - 2).execute(env);
			for (int i = sons.size() - 3; i >= 0; i--)
			{
				data = caculate(sons.at(sons.size() - 1).execute(env), data, sons.at(i).execute(env));
			}
			return data;
		}
		else if (sons.at(sons.size() - 1).isJudgement())
		{
			return Judgement(sons.at(sons.size() - 1).execute(env), sons.at(sons.size() - 2).execute(env), sons.at(sons.size() - 3).execute(env));
		}
	}
	throw InterpreteError(10);
}

Data TreeNode::caculate(Data op, Data a, Data b)
{
	return op.caculate(a, b);
}

Data TreeNode::Judgement(Data op, Data a, Data b)
{
	if (a.isJudgement() && b.isJudgement())
	{
		return op.judgement(a, b);
	}
	else
	{
		throw InterpreteError(12);
	}
}
