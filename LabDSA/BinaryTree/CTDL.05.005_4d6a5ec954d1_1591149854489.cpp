#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
using namespace std;

void printNSpace(int n)
{
	for (int i = 0; i < n - 1; i++)
		cout << " ";
}

void printInteger(int &n)
{
	cout << n << " ";
}

template <class T>
class Node
{
public:
	T data;
	Node<T> *left;
	Node<T> *right;

	Node(const T &val)
	{
		data = val;
		left = right = NULL;
	}
};

template <class T>
class BinarySearchTree
{
private:
	Node<T> *root;
	int size;

protected:
	void clearRec(Node<T> *&);
	int getHeightRec(Node<T> *);

	// TODO Methods
	bool addRec(Node<T> *&, const T &);
	bool removeRec(Node<T> *&, const T &);
	Node<T> *searchRec(Node<T> *, const T &);

public:
	BinarySearchTree()
	{
		this->root = NULL;
		this->size = 0;
	}

	~BinarySearchTree()
	{
		this->clear();
	}

	void clear();
	void printTreeStructure();
	int getHeight();

	// TODO Methods
	bool add(const T &value);
	bool remove(const T &value);
	Node<T> *search(const T &value);
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	BinarySearchTree<int> *tree = new BinarySearchTree<int>();

	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int number = stoi(line);
		tree->add(number);
	}

	cout << "After insertion:" << endl;
	tree->printTreeStructure();

	getline(ifs, line);
	size = stoi(line);
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int number = stoi(line);
		tree->remove(number);
	}

	cout << "After deletion:" << endl;
	tree->printTreeStructure();

	getline(ifs, line);
	size = stoi(line);
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int number = stoi(line);
		cout << "Search " << number << ": " << (tree->search(number) != NULL ? "Found" : "Not Found") << endl;
	}

	delete tree;

	ifs.close();

	return 0;
}
template <class T>
bool BinarySearchTree<T>::addRec(Node<T> *&node, const T &value)
{
	// TODO
Node<T>* pNew=new Node<T>(value);
	if(node==NULL) {
    node=pNew;
    return true;
  }
  if(pNew->data<node->data){
    return addRec(node->left,value);
  }else if(pNew->data>node->data){
    return addRec(node->right,value);
  }else return false;
  return false;
}

template <class T>
bool BinarySearchTree<T>::add(const T &value)
{
	// TODO
return this->addRec(this->root,value);
}

template <class T>
bool BinarySearchTree<T>::removeRec(Node<T> *&node, const T &value)
{
	// TODO

if(node==NULL) return false;
  if(node->data>value){
    return removeRec(node->left,value);
  }else if(node->data<value){
    return removeRec(node->right, value);
  }else{
    Node<T>* dlPtr=node;
    if(node->left==NULL){
      node=node->right;
      dlPtr=NULL;
      delete dlPtr;
      return true;
    }else if(node->right==NULL){
      node=node->left;
      dlPtr=NULL;
      delete dlPtr;
      return true;
    }else{
      dlPtr=node->left;
      while(dlPtr->right!=NULL){
        dlPtr=dlPtr->right;
      }
      node->data=dlPtr->data;
      return removeRec(node->left, dlPtr->data);
    }
  }
}

template <class T>
bool BinarySearchTree<T>::remove(const T &value)
{
	// 
return this->removeRec(this->root,value);
}

template <class T>
Node<T> *BinarySearchTree<T>::searchRec(Node<T> *node, const T &value)
{
	// 
if(node==NULL) return NULL;
  if(value<node->data)
    return searchRec(node->left,value);
  else if(value>node->data)
    return searchRec(node->right,value);
  else return node;
}

template <class T>
Node<T>* BinarySearchTree<T>::search(const T &value)
{
	// 
return this->searchRec(this->root,value);
}

template <class T>
int BinarySearchTree<T>::getHeightRec(Node<T> *node)
{
	if (node == NULL)
		return 0;
	int lh = this->getHeightRec(node->left);
	int rh = this->getHeightRec(node->right);
	return (lh > rh ? lh : rh) + 1;
}

template <class T>
int BinarySearchTree<T>::getHeight()
{
	return this->getHeightRec(this->root);
}

template <class T>
void BinarySearchTree<T>::clearRec(Node<T> *&node)
{
	if (node != NULL)
	{
		this->clearRec(node->left);
		this->clearRec(node->right);
		delete node;
		node = NULL;
	}
}

template <class T>
void BinarySearchTree<T>::clear()
{
	this->clearRec(this->root);
	this->size = 0;
}

template <class T>
void BinarySearchTree<T>::printTreeStructure()
{
	int height = this->getHeight();

	if (this->root == NULL)
	{
		cout << "NULL\n";
		return;
	}
	queue<Node<T> *> q;
	q.push(root);
	Node<T> *temp;
	int count = 0;
	int maxNode = 1;
	int level = 0;
	int space = pow(2, height);
	printNSpace(space / 2);
	while (!q.empty())
	{
		temp = q.front();
		q.pop();

		if (temp == NULL)
		{
			cout << " ";
			q.push(NULL);
			q.push(NULL);
		}
		else
		{

			cout << temp->data;
			q.push(temp->left);
			q.push(temp->right);
		}
		printNSpace(space);
		count++;
		if (count == maxNode)
		{
			cout << endl;
			count = 0;
			maxNode *= 2;
			level++;
			space /= 2;
			printNSpace(space / 2);
		}
		if (level == height)
			return;
	}
}