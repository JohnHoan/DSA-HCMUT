#include "main.h"
#include "processData.h"

using namespace std;
void usage();


int main(int argc, char** argv) {
	ifstream inFile;
	ofstream outFile;
    
	if (argc != 3){
        usage();
        return EXIT_FAILURE;
    }
	
	inFile.open(argv[1]);
	if (!inFile) {
        cout << "Unable to open file " << argv[1];
        return EXIT_FAILURE; // terminate with error
    }
	
    outFile.open(argv[2]);	
	if (!outFile) {
        cout << "Unable to open file " << argv[2];
        return EXIT_FAILURE; // terminate with error
    }
    
    ProcessData * data = new ProcessData();
	
    string line;
    while (getline(inFile, line)) { 
    	outFile << data->process(line) << endl;
    }
    
    inFile.close();
    outFile.close();
    delete data;

	return EXIT_SUCCESS;
}
void usage() {
	cout << "Usage: main <input file> <output file>" << endl;
}