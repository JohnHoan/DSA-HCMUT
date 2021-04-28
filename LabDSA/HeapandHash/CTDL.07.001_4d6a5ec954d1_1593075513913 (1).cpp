#include <iostream>
#include <fstream>
#include <math.h>
#define MAX_SIZE 1000
using namespace std;

template <class T>
class MaxHeap {
private:
	T arr[MAX_SIZE];
	int count;

protected:
	void reHeapUp(int pos);
	void reHeapDown(int pos);
public:
	MaxHeap();
	bool insert(T& valIn);
	bool remove(T& valOut);
	void print();
	T* toArray();
	int getSize();

	void buildHeap(T* a, int size);
	void printValuesLargerThan(T k);
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	MaxHeap<int> *heap = new MaxHeap<int>();
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int element = stoi(line);
		heap->insert(element);
	}
	cout << "After insertion: ";
	heap->print();

	getline(ifs, line);
	int numOfDel = stoi(line);

	cout << "Remove: ";
	for (int i = 0; i < numOfDel; i++) {
		int element = 0;
		heap->remove(element);
		cout << element << " ";
	}

	cout << endl << "After removal: ";
	heap->print();

	delete heap;

	ifs.close();

	return 0;
}


template <class T>
void MaxHeap<T>::reHeapUp(int position) {
	// TODO
	if(position>0){
    int parent=(position-1)/2;
    if(arr[position]>arr[parent]){
      swap(arr[position],arr[parent]);
      //swap(position,parent);
      reHeapUp(parent);
    }
  }
}

template <class T>
void MaxHeap<T>::reHeapDown(int position) {
	// TODO
	int leftChild=position*2+1;
  int rightChild=position*2+2;
  int large;
  int lastposition=this->count-1;
  if(leftChild<=lastposition){
    if(rightChild<=lastposition&&arr[rightChild]>arr[leftChild]){
      large=rightChild;
    }else{
      large=leftChild;
    }
    if(arr[large]>arr[position]){
      swap(arr[large],arr[position]);
      //swap(large,position);
      reHeapDown(large);
    }
  }
}

template <class T>
T* MaxHeap<T>::toArray() {
	return arr;
}

template <class T>
int MaxHeap<T>::getSize() {
	return count;
}

template <class T>
bool MaxHeap<T>::insert(T& valIn) {
	// TODO
  int last=getSize()-1;
	if(last==MAX_SIZE) return false;
  this->count++;
  last=last+1;
  arr[last]=valIn;
  reHeapUp(last);
  return true;
}

template <class T>
MaxHeap<T>::MaxHeap() {
	count = 0;
}

template <class T>
bool MaxHeap<T>::remove(T& valOut) {
	// TODO
  int last=getSize()-1;
	if(last==0) return false;
  valOut=arr[0];
  arr[0]=arr[last];
  last=last-1;
  this->count--;
  reHeapDown(0);
  return true;
}

template <class T>
void MaxHeap<T>::print() {
	for (int i = 0; i < count; i++)
		cout << arr[i] << " ";
	cout << endl;
}