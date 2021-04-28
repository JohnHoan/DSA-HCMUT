#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "01.004_sol.cpp"
using namespace std;

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto"} even in the comments */

//----------------------------------------------
// Begin implementation
//----------------------------------------------

/// Student implement the recursive function here
int isEvenWord(string word) {
	size_t pos=word.find(word[0],1);
static int count=0;
if(word.length()==0) return count;
if(pos>0&&pos<word.length()){
    word.erase(word.begin()+pos);
    word.erase(word.begin()+0);
    count++;
    return isEvenWord(word);
}
else return -1;
}


bool codeCheck() {
    const char* forbiddenKeyword[] = {"include", "while", "for", "goto"};
    fstream ifs;
    ifs.open("main.cpp", ios::in);
    if (ifs.fail()) ifs.open(FILENAME, ios::in);
    if (ifs.fail()) return true;
    ifs.seekg(0, ifs.end);
    int fileSize = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    char* fileContent = new char[fileSize];
    ifs.read(fileContent, fileSize);
    ifs.close();
    *strstr(fileContent, "bool codeCheck() {") = '\0';
    char* todoSegment = strstr(fileContent ,"// Begin implementation");
    int numberOfForbiddenKeyword = sizeof(forbiddenKeyword) / sizeof(const char*);
    for (int i = 0; i < numberOfForbiddenKeyword; i++) { if (strstr(todoSegment, forbiddenKeyword[i])) return false; }
    delete[] fileContent;
    return true;
}


int main(int argc, char** argv) {
	if (codeCheck() == false) {
        cout << "Forbidden-keyword rule violation." << endl;
        return -1;
    }

    ifstream ifs;
	ifs.open(argv[1], ifstream::in);
	
	string word;
    getline(ifs, word);

	ifs.close();

	cout << isEvenWord(word);

	return 0;

}