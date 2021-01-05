#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Tree.h"
#include "Codereader.h"
#include "enviroment.h"
using namespace std;
static environment highestEnv;
int main()
{
	cout << "Welcome to use LISP language" << endl;
	cout << "Enter \" Esc \" to exit" << endl;
	cout << "Enter \" syntax \" to query the LISP language language" << endl;
	cout << "Please enter the LISP statement you want to process: " << endl;
	string b = "";
	getline(cin, b);
	while (b != "Esc")
	{
		try
		{
			if (b == "syntax")
			{
				cout << "((函数) （变量）)" << endl;
				cout << "(define (函数名、 变量名、 变量名、 变量名、 ···) (函数式))" << endl;
				cout << "(if (判断式) (函数1) (函数2))" << endl;
				cout << "(lambda (变量名) (函数式) (函数)) 此处函数将赋值给变量" << endl;
				cout << "(setq （变量名.已生成） （函数）) 此处函数将赋值给变量" << endl;
				cout << "Please enter the LISP statement you want to process: (or enter \"Esc\" to exit)" << endl;
				getline(cin, b);
			}
			else
			{
				Codereader a(b);
				Tree tree(a);
				while (!tree.toisstand())
				{
					cout << "Enter fewer close brackets than open brackets" << endl;
					cout << "Please continue typing: " << endl;
					string str;
					getline(cin, str);
					b = b + str;
					Codereader c(b);
					tree = tree.generateTree(c);
				}
				TreeNode node = tree.show();
				Data data = node.execute(highestEnv);
				data.toString();
				cin.clear();
				cout << "Please enter the LISP statement you want to process: (or enter \"Esc\" to exit)" << endl;
				getline(cin, b);
			}
		}
		catch (InterpreteError ex)
		{
			if (ex.show() == 1)
			{
				cout << "The parentheses do not agree" << endl;
			}
			else if (ex.show() == 2)
			{
				cout << "Cannot calculate correctly" << endl;
			}
			else if (ex.show() == 3)
			{
				cout << "Strings cannot be compared" << endl;
			}
			else if (ex.show() == 4)
			{
				cout << "Error in function definition" << endl;
			}
			else if (ex.show() == 5)
			{
				cout << "Variable setting error" << endl;
			}
			else if (ex.show() == 6)
			{
				cout << "Error using Cond function" << endl;
			}
			else if (ex.show() == 7)
			{
				cout << "Error in judging format" << endl;
			}
			else if (ex.show() == 8)
			{
				cout << "Subenvironment fetch error" << endl;
			}
			else if (ex.show() == 9)
			{
				cout << "Incorrect use of Let function" << endl;
			}
			else if (ex.show() == 10)
			{
				cout << "Statement input error" << endl;
			}
			else if (ex.show() == 11)
			{
				cout << "Incorrect number of function variables" << endl;
			}
			else if (ex.show() == 12)
			{
				cout << "Incorrect use of judgment" << endl;
			}
			else if (ex.show() == 13)
			{
				cout << "No assigned variable was found" << endl;
			}
			else if (ex.show() == 14)
			{
				cout << "Error setting function variable" << endl;
			}
			cin.clear();
			cout << "Please reenter the correct LISP statement: (or enter \"Esc\" to exit)" << endl;
			getline(cin, b);
		}
	}
	
}
