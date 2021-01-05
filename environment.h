#pragma once
#include <string>
#include <map>  
#include <vector>
#include "data.h"
#include "exception1.h"
using namespace std;
class environment
{
private:
	map<string, Data> localDict;
	vector<environment> father;
	int layer;
public:
	environment() {}
	environment(const  environment & fatherEnv);
	environment(map<string, Data> map, environment fatherEnv);
	Data search(string key);
	map<string, Data> showLocalDict();
	vector<environment> showFather();
	int showLayer();
	void erase(string key);
	environment put(string key, Data val);
	environment set(string key, Data val);
	environment & operator = (const environment & env);
	environment setFather(environment father);
	friend map<string, Data> add(map<string, Data> map1, map<string, Data> map2);
};

map<string, Data> add(map<string, Data> map1, map<string, Data> map2)
{
	map<string, Data>::iterator i;
	i = map2.begin();
	while (i != map2.end())
	{
		map1.insert(map<string, Data> ::value_type(i->first, i->second));
		i++;
	}
	return map1;
}

environment & environment::operator = (const environment & env)
{
	localDict = env.localDict;
	father = env.father;
	layer = env.layer;
	return *this;
}

environment::environment(const environment & fatherEnv)
{
	this->localDict = fatherEnv.localDict;
	this->father = fatherEnv.father;
	this->layer = fatherEnv.layer;
}



environment::environment(map<string, Data> map, environment fatherEnv)
{
	localDict = add(localDict,map);
	this->father.push_back(fatherEnv);
	this->layer = fatherEnv.layer;
}

Data environment::search(string key)
{
	if (!localDict.empty())
	{
		map<string, Data>::iterator i = localDict.find(key);
		if (i != localDict.end())
		{
			return i -> second;
		}
		else 
		{
			if (father.begin() == father.end()) 
			{
				return Data();
			}
			else if (father[0].showLocalDict().empty())
			{
				return Data();
			}
			else {
				return father[0].search(key);
			}
		}
	}
	return Data();
}

map<string, Data> environment::showLocalDict()
{
	return localDict;
}

vector<environment> environment::showFather()
{
	return father;
}

int environment::showLayer()
{
	return layer;
}

void environment::erase(string key)
{
	map<string, Data>::iterator i;
	if (localDict.find(key) == localDict.end())
	{
		throw  InterpreteError(13);
		
	}
	else
	{
		i = localDict.find(key);
		localDict.erase(i);
	}
}

environment environment::put(string key, Data val)
{
	localDict.insert(map<string, Data> ::value_type(key, val));
	return *this;
}

environment environment::set(string key, Data val)
{
	environment env = *this;
	while (env.localDict.count(key) == 0)
	{
		if (father.begin() == father.end())
		{
			throw  InterpreteError(13);
		}
		else
		{
			env = env.father[0];
		}
	}
	map<string, Data>::iterator i = localDict.find(key);
	localDict.erase(i);
	env.localDict.insert(map<string, Data> ::value_type(key, val));
	return env;
}

environment environment::setFather(environment father)
{
	this->father.push_back(father);
	return *this;
}
