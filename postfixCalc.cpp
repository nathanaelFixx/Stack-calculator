//____________________
//Nathanael Fixx
//CSS 342 - Project 3
//17 hours
//Cygwin
//____________________

#include <iostream>
#include "LLStack.h"
#include "LLStack.cpp"
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

void calculate(LLStack<int>test);
void calculate(string filename, LLStack<int>test);

int main(int argc, char *argv[])
{

	LLStack<int>test;
	LLStack<int>test2;


	if (argc == 2) {
		string str(argv[1]);
		calculate(str, test);
	}
	
	else {
		calculate(test);
	}

	return 0;
}
//___________________________
//Reading from console window
//___________________________
void calculate(LLStack<int>test)
{
	string input;
	int splitInput;
	char check = ' ';
	int temp;
	int temp2;
	int final;

  cout << "Please enter your numbers: ";
					//checks if at end of line
    while (cin.peek() != '\n' && cin.peek() != '\r') { 

	cin >> check;
				                                       
		//if character is an operator, perform the operation on the 
		//last two numbers on the stack. Otherwise, 
		//put it back in the stream.
	  if (check != '/' && check != '*' && check != '+' && check != '-') {
			  cin.putback(check);
			  cin >> splitInput;
			  test.push(splitInput);
			}

			else {
				//if there is more than one element in the
				//stack, decide which operation to perform
				//based on which operator it is.
			  if (test.size() > 1) {

				if (check == '/') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 / temp;
					test.push(final);
				}

				else if (check == '-') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 - temp;
					test.push(final);
					}

				else if (check == '*') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 * temp;
					test.push(final);
				}

				else if (check == '+') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 + temp;
					test.push(final);
					}
				}
				else {
					cout << "ERROR!" << endl;
					return;
				}
			}
		}

		if (test.size() != 1)
			cout << "ERROR!" << endl;
		else
			cout << test.top() << endl;
	}
//____________________
//Reading from file
//____________________
void calculate(string filename, LLStack<int>test)
{

	ifstream fin;
	fin.open(filename);

	if (fin.fail())
	{
		cout << "failed";
	}

	int i;
	char check;
	int temp = 0;
	int temp2;
	int final;



  while (fin >> check) {
	if (check != '/' && check != '*' && check != '+' && check != '-') {
		fin.putback(check);
		fin >> i;
		test.push(i);
		}
		else {
			if (test.size() > 1) {
				if (check == '/') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 / temp;
					test.push(final);
				}

				else if (check == '-') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 - temp;
					test.push(final);
				}

				else if (check == '*') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 * temp;
					test.push(final);
				}

				else if (check == '+') {
					temp = test.top();
					test.pop();
					temp2 = test.top();
					test.pop();
					final = temp2 + temp;
					test.push(final);
				}
			}
			else {
				cout << "ERROR!" << endl;
				return;
			}
		}
	}

	if (test.size() != 1)
		cout << "ERROR!" << endl;
	else
	cout << test.top() << endl;
}



