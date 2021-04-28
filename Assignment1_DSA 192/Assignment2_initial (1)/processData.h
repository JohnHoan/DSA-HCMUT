#include "dbLib.h"

class ProcessData
{
private:
	static const int MAXSIZECODE = 8;
	static int split(string line, string *&sp);

public:
	ProcessData();
	~ProcessData();
	int process(string line);
	int insert(const string *sp, const int n);
};