#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
using namespace std;

bool checkParentheses(const char *arr)
{
	  stack<char> v;
  if(arr==NULL) return true;
  for(int i = 0; arr[i] != '\0'; i++){
    if(arr[i] == '(' || arr[i] == '{' || arr[i] == '['){
      v.push(arr[i]);
    }
    else if(arr[i] == ')'){
      if(v.empty() || v.top() != '('){
        return false;
      }
      v.pop();
    }
    else if(arr[i] == '}'){
      if(v.empty() || v.top() != '{'){
        return false;
      }
    v.pop();
    }
    else{
      if(v.empty() || v.top() != '['){
        return false;
      }
    v.pop();
    }
  }
  return v.empty();
}

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string arr;
	getline(ifs, arr);

	cout << checkParentheses(arr.c_str());

	ifs.close();

	return 0;
}
