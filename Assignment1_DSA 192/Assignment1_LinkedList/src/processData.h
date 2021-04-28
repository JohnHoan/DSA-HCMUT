#include "main.h"
class Exchange {
	
};
template <typename T>
class Link {
	public:
		T data;
		Link<T>* next;
		Link<T>(const Link<T>& n=nullptr) {next = n;} 
		Link<T>(const T& ele, const Link<T>& n=nullptr) {
			data = ele;
			next = n;
		}
};
template <typename T>
class List {
  // Return: The number of elements in the list.
  	virtual int length() const = 0;
	virtual void insert(const T& ele) = 0;	
};
template <typename T>
class LList: public List<T> {
	private:
		Link<T>* head;
		Link<T>* last;
		Link<T>* curr;
		int cnt;
	public:
		LList() {head = last = curr = new Link<T>();}
		int length() const {return cnt;}
		void insert(const T& ele) {
			curr->next = new Link(ele,curr->next);
		}
};

class ProcessData {
	private:
		List<Exchange> * data;
		static const int MAXSIZECODE = 8;
		static int split(string line,string* &sp);
	public:
		ProcessData();
		~ProcessData();
		int process(string line);
		int insert(const string* sp,const int n);
};