/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List();

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
    }
    void    traverse(void (*op)(T&, void*), void* pParam) { //process find
        // TODO: Your code goes here
    }

	//return pointer pHead
	L1Item<T>* getHead() {
		return this->_pHead;
	}
};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
	if (this->isEmpty()) {
		L1Item<T>* L1ItemNew = new L1Item<T>(a);
		this->_pHead = L1ItemNew;
		this->_size++;
	}
	else {
		L1Item<T>* L1ItemNew = new L1Item<T>(a);
		L1Item<T>* curL1Item = this->_pHead;
		while (curL1Item->pNext != NULL) {
			curL1Item = curL1Item->pNext;
		}
		curL1Item->pNext = L1ItemNew;
		this->_size++;
	}
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
	if (this->isEmpty()) {
		L1Item<T>* L1ItemNew = new L1Item<T>(a);
		this->_pHead = L1ItemNew;
		this->_size++;
	}
	else {
		L1Item<T>* L1ItemNew = new L1Item<T>(a);
		L1ItemNew->pNext = this->_pHead;
		this->_pHead = L1ItemNew;
		this->_size++;
	}
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
	if (this->isEmpty() == false) {
		L1Item<T>* curL1Item = this->_pHead;
		this->_pHead = curL1Item->pNext;
		curL1Item = NULL;
		delete curL1Item;
		this->_size--;
		return 0;
	}
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
	if (this->isEmpty() == false) {
		L1Item<T>* curL1Item = this->_pHead;
		L1Item<T>* preL1Item = curL1Item;
		while (curL1Item->pNext != NULL) {
			preL1Item = curL1Item;
			curL1Item = curL1Item->pNext;
		}
		preL1Item->pNext = curL1Item->pNext;
		curL1Item = NULL;
		delete curL1Item;
		this->_size--;
		return 0;
	}
    // TODO: Your code goes here
    return -1;
}

template<class T>
void L1List<T>::clean() {
	if (this->_pHead == NULL)return;
	L1Item<T>* curItem = this->_pHead;
	while (curItem != NULL) {
		this->_pHead = curItem->pNext;
		curItem = NULL;
		delete curItem;
		curItem = this->_pHead;
	}
}

template<class T>
L1List<T>::~L1List() {
	this->clean();
}

template<class T>
T& L1List<T>::at(int i) {
	L1Item<T>* cur = this->_pHead;
	int count = 0;
	while (count < i) {
		count++;
		cur = cur->pNext;
	}
	T& _data = cur->data;
	return _data;
}

template<class T>
T& L1List<T>::operator[](int i) {
	return this->at(i);
}

template<class T>
bool L1List<T>::find(T& a, int& idx) {
	if (this->isEmpty()) {
		idx = -1;
		return false;
	}
	int index = 0;
	L1Item<T>* pWalker = this->_pHead;
	while (index < this->_size) {
		if (pWalker->data == a) {
			idx = index;
			return true;
		}
		pWalker = pWalker->pNext;
		index++;
	}
	idx = -1;
	return false;
}

template<class T>
int L1List<T>::insert(int i, T& a) {
	if (this->_pHead == NULL || i > int(this->_size))return -1;
	if (i == 0) return this->insertHead(a);
	else {
		int count = 0;
		L1Item<T>* L1ItemNew = new L1Item<T>(a);
		L1Item<T>* curL1Item = this->_pHead;
		while (count < i - 1) {
			count++;
			curL1Item = curL1Item->pNext;
		}
		L1ItemNew->pNext = curL1Item->pNext;
		curL1Item->pNext = L1ItemNew;
		this->_size++;
		return 0;
	}
	return -1;
}

template<class T>
int L1List<T>::remove(int i) {
	if (this->_pHead == NULL || i > int(this->_size))return -1;
	if (i == 0)return this->removeHead();
	else {
		L1Item<T>* curL1Item = this->_pHead;
		L1Item<T>* preL1Item = curL1Item;
		int count = 0;
		while (count < i) {
			count++;
			preL1Item = curL1Item;
			curL1Item = curL1Item->pNext;
		}
		preL1Item->pNext = curL1Item->pNext;
		curL1Item = NULL;
		delete curL1Item;
		this->_size--;
		return 0;
	}
	return -1;
}

template<class T>
void L1List<T>::reverse() {
	if (this->_size <= 1)return;
	L1Item<T>* pre = NULL;
	L1Item<T>* cur = this->_pHead;
	L1Item<T>* next = cur->pNext;
	while (cur != NULL) {
		next = cur->pNext;
		cur->pNext = pre;
		pre = cur;
		cur = next;
	}
	this->_pHead = pre;
}



#endif //DSA191_A1_DSALIB_H