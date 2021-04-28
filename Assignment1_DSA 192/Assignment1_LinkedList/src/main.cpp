#include "main.h"
#include "processData.h"

using namespace std;
void usage();


int main(int argc, char** argv) {
	ifstream inFile;
	ofstream outFile;
	
	if (argc != 3)
		usage();
	
	inFile.open(argv[1]);
	if (!inFile) {
        cout << "Unable to open file " << argv[1];
        exit(1); // terminate with error
    }
	
    outFile.open(argv[2]);	
	if (!outFile) {
        cout << "Unable to open file " << argv[2];
        exit(1); // terminate with error
    }
    
    ProcessData * data = new ProcessData();
	
    string line;
    while (getline(inFile, line)) { 
    	outFile << data->process(line) << endl;
    }
    
    inFile.close();
    outFile.close();
    delete data;

	return 0;
}
void usage() {
	cout << "Usage: main <input file> <output file>" << endl;
	exit(1);
}