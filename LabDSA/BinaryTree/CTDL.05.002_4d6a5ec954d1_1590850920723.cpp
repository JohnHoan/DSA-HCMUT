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
class BinaryTree
{
private:
	Node<T> *root;
	int size;

protected:
	void clearRec(Node<T> *&);
	void constructFromArrayRec(Node<T> *&, int, T **&, int n);

	// TODO Methods
	int getHeightRec(Node<T> *);
	int countTwoChildrenNodesRec(Node<T> *);

public:
	BinaryTree()
	{
		this->root = NULL;
		this->size = 0;
	}

	~BinaryTree()
	{
		this->clear();
	}

	void clear();
	void constructFromArray(T **&, int n);
	void printTreeStructure();

	// TODO Methods
	int getHeight();
	int countTwoChildrenNodes();
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string element;
	getline(ifs, element);
	int size = stoi(element);

	int **data = new int *[size];

	for (int i = 0; i < size; i++)
	{

		getline(ifs, element);

		if (element != "NULL")
		{
			data[i] = new int;
			*(data[i]) = stoi(element);
		}
		else
			data[i] = NULL;
	}

	BinaryTree<int> *tree = new BinaryTree<int>();
	tree->constructFromArray(data, size);
	tree->printTreeStructure();

	cout << "The number of nodes with two children: " << tree->countTwoChildrenNodes();

	delete tree;

	ifs.close();

	return 0;
}

template <class T>
int BinaryTree<T>::countTwoChildrenNodesRec(Node<T> *node)
{
	// TODO
	static int count=0;
  if(node!=NULL){
    if(node->left!=NULL&&node->right!=NULL) count++;
    countTwoChildrenNodesRec(node->left);
    countTwoChildrenNodesRec(node->right);
  }
  return count;
}

template <class T>
int BinaryTree<T>::countTwoChildrenNodes()
{
	// TODO
this->countTwoChildrenNodesRec(this->root);
}

template <class T>
int BinaryTree<T>::getHeightRec(Node<T> *node)
{
	// TODO
  if(node==NULL) return 0;
  else{
    int max1=getHeightRec(node->left);
    int max2=getHeightRec(node->right);
    if(max1>max2) return max1+1;
    return max2+1;
  }
}

template <class T>
int BinaryTree<T>::getHeight()
{
	// TODO
return this->getHeightRec(this->root);
}

template <class T>
void BinaryTree<T>::clearRec(Node<T> *&node)
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
void BinaryTree<T>::clear()
{
	this->clearRec(this->root);
	this->size = 0;
}

template <class T>
void BinaryTree<T>::constructFromArrayRec(Node<T> *&node, int index, T **&array, int n)
{
	if (index < n)
	{
		if (array[index] == NULL)
		{
			node = NULL;
		}
		else
		{
			Node<T> *temp = new Node<T>(*(array[index]));
			node = temp;
			this->size++;

			this->constructFromArrayRec(node->left, 2 * index + 1, array, n);
			this->constructFromArrayRec(node->right, 2 * index + 2, array, n);
		}
	}
}

template <class T>
void BinaryTree<T>::constructFromArray(T **&array, int n)
{
	this->clear();
	this->constructFromArrayRec(this->root, 0, array, n);
}

template <class T>
void BinaryTree<T>::printTreeStructure()
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