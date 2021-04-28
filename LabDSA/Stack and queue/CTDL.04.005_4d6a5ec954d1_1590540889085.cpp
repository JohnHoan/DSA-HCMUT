#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
using namespace std;

int evaluate(char x, int op1, int op2)
{
	// TODO
}

int evaluatePrefixExpression(const char *exp)
{
	 string exp1=string(exp);
  // create an empty stack
	stack<int> stack;

	// traverse the given expression
	for (int i = exp1.length()-1; i >=0; i--)
	{
		// if current char is an operand, push it to the stack
		if (exp1[i] >= '0' && exp1[i] <= '9') {
			stack.push(exp1[i] - '0');
		}
		// if current char is an operator
		else
		{
			// pop top two elements from the stack
			int x = stack.top();
			stack.pop();

			int y = stack.top();
			stack.pop();

			// evaluate the expression x op y, and push the
			// result back to the stack
			if (exp1[i] == '+')
				stack.push(x+y);

			else if (exp1[i] == '-')
				stack.push(x-y);

			else if (exp1[i] == '*')
				stack.push(x*y);

			else if (exp1[i] == '/'){
        if(y == 0)
          throw "Division by zero condition!";
        stack.push(x/y);
      }
      else throw "input exception";
		}
	}

	// At this point, the stack is left with only one element
	// i.e. expression result
	return stack.top();

}

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string arr;
	getline(ifs, arr);

	try
	{
		cout << evaluatePrefixExpression(arr.c_str());
	}
	catch (const char *msg)
	{
		cout << msg;
	}

	ifs.close();

	return 0;
}
