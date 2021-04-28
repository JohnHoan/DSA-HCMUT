#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "01.003_sol.cpp"
using namespace std;

/* Your code MUST NOT contain any of words in the list:
{"include", "for",  "while", "goto"} even in the comments */

//----------------------------------------------
// Begin implementation
//----------------------------------------------

/* Write the recursive function returning the max value in the array */
int recursiveMax(int* arr, int numberOfElements) {
    if(numberOfElements==1) return arr[numberOfElements-1];
if(arr[numberOfElements-1]<=arr[numberOfElements-2]){
  return recursiveMax(arr, numberOfElements-1);
}
else{
    arr[numberOfElements-2]=arr[numberOfElements-1];
    return recursiveMax(arr,numberOfElements-1);
}
}


bool codeCheck() {
    const char* forbiddenKeyword[] = {"include", "for",  "while", "goto"};
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

int main(int argc, char* argv[]) {
    if (codeCheck() == false) {
        cout << "Forbidden-keyword rule violation." << endl;
        return -1;
    }
    // Section: read testcase
    ///Student may comment out this section for local testing
    if (argc < 2) return 0;
    ifstream fileIn;
    try {
        fileIn.open(argv[1]);
        if (fileIn.fail()) throw "Failed to open file.";
        int numberOfElements;
        fileIn >> numberOfElements;
        int* arr = new int[numberOfElements];
        for (int i = 0; i < numberOfElements; i++) {
            fileIn >> arr[i];
        }
        cout << recursiveMax(arr, numberOfElements);
        delete[] arr;
        fileIn.close();
    }
    catch (const char* errMsg){
        cerr << errMsg;
    }
    // Endsection: read testcase
    //------------------------------------
    return 0;
}
