#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

bool isDuckNumber(int n) {
	while(n!=0){
    int x=n%10;
    if(x==0) return true;
    n=n/10;
}
return false;
}

int main(int narg, char **argv)
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);
	
	int n;
	string line;

	for (int count = 0; ifs.good() && count < 1; count++) {
		getline(ifs, line);
		n = stoi(line);
	}
	ifs.close();
	
    cout << isDuckNumber(n);
	return 0;
}