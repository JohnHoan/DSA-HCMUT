#include "dbLib.h"

class ProcessData
{
private:
  string money;
  string leverage;
  CurrencyList* data;
	static const int MAXSIZECODE = 8;
	static int split(string line, string *&sp);

public:
  void setMoney(string Money){
    this->money=Money;
  }
  string getMoney(){
    return this->money;
  }
  void setLeverage(string Leverage){
    this->leverage=Leverage;
  }
  string getLeverage(){
    return this->leverage;
  }
  map<string,string> mapID;
  map<string,string> myMapPairCurrency;
	ProcessData();
	~ProcessData();
	int process(string line);
	int insert(const string *sp, const int n);
  int update(const string *sp, const int n);
  int remove(const string *sp, const int n);
  int sdFuction(const string *sp, const int n);
  int cdFuction(const string *sp, const int n);
  int slFuction(const string *sp, const int n);
  int obFuction(const string *sp, const int n);
  int osFuction(const string *sp, const int n);
  int cbFuction(const string *sp, const int n);
  int csFuction(const string *sp, const int n);
};