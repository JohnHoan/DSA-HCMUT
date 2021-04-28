#include "main.h"
enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};
struct ExchangeRate{
  string time;
  string BP;
  string AP;
};
struct Node_Exrate{
  ExchangeRate data;
  Node_Exrate *left;
  Node_Exrate *right;
  BalanceValue balance;
	Node_Exrate(ExchangeRate &val)
	{
		data = val;
		left = right = NULL;
		balance = EH;
	}
};
class AVL{
  Node_Exrate *root;
  int count;
  protected:
  void clearRec(Node_Exrate *&);
  Node_Exrate *rotateRight(Node_Exrate *&node);
	Node_Exrate *rotateLeft(Node_Exrate *&node);
	Node_Exrate *leftBalance(Node_Exrate *&node, bool &taller);
	Node_Exrate *rightBalance(Node_Exrate *&node, bool &taller);
  Node_Exrate *removeLeftBalance(Node_Exrate *&node, bool &shorter);
	Node_Exrate *removeRightBalance(Node_Exrate *&node,bool &shorter);
  Node_Exrate *removeRec(Node_Exrate *&node, const string &value, bool &shorter, bool &success);
  Node_Exrate *insertRec(Node_Exrate *&node, ExchangeRate &value, bool &taller);
  Node_Exrate *searchRec(Node_Exrate *&node,const string &value);
  void findRangeTimeRec(Node_Exrate *&node, string &time1, string &time2);
  string findMaxTimeForN(Node_Exrate *&node,string &value);
  public:
  map<int, string> myTime;
  AVL()
	{
		this->root = NULL;
    this->count=0;
	}
	~AVL()
	{
		this->clear();
	}
  int getRootData(){
    if(this->root==NULL) return -1;
    string timeRoot=this->root->data.time;
    return stoi(timeRoot);
  }
  bool isEmpty(){
    if(this->root==NULL) return true;
    return false;
  }
  int getCount(){
    return this->count;
  }
  void clear();
  void insert(ExchangeRate &value);
  void remove(const string &value);
  Node_Exrate *search(const string &value);
  void findTime(string &time1, string &time2);
  string findMaxTime(string &value);

	//void remove(ExchangeRate &value);
  
};

struct CurrencyData{
  string BC;
  string QC;
  AVL* AVLTree=new AVL();
};
struct CurrencyNode{
  CurrencyData currency_data;
  CurrencyNode* link;
  CurrencyNode():link(NULL){}
  CurrencyNode(CurrencyData& a):currency_data(a),link(NULL){}
};
class CurrencyList{
  CurrencyNode* head;
  int count;
  public:
  CurrencyList():head(NULL),count(0){}
  ~CurrencyList();
  CurrencyNode* getHead(){return head;}
  bool isEmpty(){return head==NULL;}
  int length(){return count;}
  void clean();
  bool find(string BC, string QC, int &idx);
  int insert_currency(CurrencyData& a);
};
