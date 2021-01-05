#pragma once
#include "TreeNode.h"
#include<queue>
#include <deque>
#include "Codereader.h"
#include<stack> 
class Tree
{
private:
	Codereader in;
	deque<TreeNode> stack;
	TreeNode root;
	bool isstand = true;;
	
public:
	Tree() {}
	Tree(Codereader input);
	TreeNode generateNode(Node s);
	TreeNode getParentNode() 
	{
		return TreeNode(" ");
	}
	Tree generateTree(Codereader input);
	TreeNode show();
	bool toisstand();
};

Tree::Tree(Codereader input)
{
	if (input.isstandard() != 3)
	{
		root = generateNode(input.manage());
		if (!root.isempty())
		{
			stack.push_front(root);
			while (input.showindex() < input.showlength())
			{
				Node val = input.manage();
				if (")" == val.show())
				{
					root = getParentNode();
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
					stack.push_front(generateNode(val));
				}
			}
		}
		else
		{
			isstand = false;
		}
	}
	else
	{
		root = generateNode(input.manage());
		if (!root.isempty())
		{
			stack.push_front(root);
			while (input.showindex() < input.showlength())
			{
				Node val = input.manage();
				if (")" == val.show())
				{
					root = getParentNode();
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
					stack.push_front(generateNode(val));
				}
			}
		}
		else
		{
			isstand = false;
		}
		root = getParentNode();
		TreeNode tmp = stack.front();
		stack.pop_front();
		while (!stack.empty())
		{
			root = root.grabFather(tmp);
			tmp = stack.front();
			stack.pop_front();
		}
		root = root.grabFather(tmp);
		stack.push_front(root);
	}
}

Tree Tree::generateTree(Codereader input)
{
	root = generateNode(input.manage());
	if (!root.isempty())
	{
		stack.push_front(root);
		while (input.showindex() < input.showlength())
		{
			Node val = input.manage();
			if (")" == val.show())
			{
				root = getParentNode();
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
				stack.push_front(generateNode(val));
			}
		}
		isstand = true;
	}
	else
	{
		isstand = false;
	}
	return *this;
}


TreeNode Tree::generateNode(Node s) 
{
	if (s.toisstand())
	{
		return TreeNode(s);
	}
	else
	{
		return TreeNode();
	}
	
}

TreeNode Tree::show()
{
	return root;
}

bool Tree::toisstand()
{
	return isstand;
}
