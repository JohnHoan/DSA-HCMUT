#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
using namespace std;

enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};

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
	BalanceValue balance;

	Node(const T &val)
	{
		data = val;
		left = right = NULL;
		balance = EH;
	}
};

template <class T>
class AVL
{
private:
	Node<T> *root;

protected:
	void clearRec(Node<T> *&);
	int getHeightRec(Node<T> *);
	Node<T> *rotateRight(Node<T> *&node);
	Node<T> *rotateLeft(Node<T> *&node);
	Node<T> *leftBalance(Node<T> *&node, bool &taller);
	Node<T> *rightBalance(Node<T> *&node, bool &taller);
	Node<T> *removeLeftBalance(Node<T> *&node, bool &shorter);
	Node<T> *removeRightBalance(Node<T> *&node, bool &shorter);

	//TODO Methods
	Node<T> *insertRec(Node<T> *&node, const T &value, bool &taller);
	Node<T> *removeRec(Node<T> *&node, const T &value, bool &shorter, bool &success);

public:
	AVL()
	{
		this->root = NULL;
	}

	~AVL()
	{
		this->clear();
	}

	void clear();
	int getHeight();
	void printTreeStructure();

	// TODO Methods
	void insert(const T &value);
	void remove(const T &value);
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	AVL<int> *tree = new AVL<int>();
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		tree->insert(stoi(line));
	}

	cout << "After insertion: " << endl;
	tree->printTreeStructure();

	getline(ifs, line);
	size = stoi(line);

	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int number = stoi(line);
		tree->remove(number);
		cout << "After delete " << number << ":" << endl;
		tree->printTreeStructure();
	}

	delete tree;

	ifs.close();

	return 0;
}

template <class T>
Node<T> *AVL<T>::rotateRight(Node<T> *&node)
{
	Node<T> *temp = node->left;
	node->left = temp->right;
	temp->right = node;
	node = temp;
	return node;
}

template <class T>
Node<T> *AVL<T>::rotateLeft(Node<T> *&node)
{
	Node<T> *temp = node->right;
	node->right = temp->left;
	temp->left = node;
	node = temp;
	return node;
}

template <class T>
Node<T> *AVL<T>::insertRec(Node<T> *&node, const T &value, bool &taller)
{
	if (node == NULL)
	{
		node = new Node<T>(value);
		taller = true;
		return node;
	}

	if (value < node->data)
	{
		node->left = this->insertRec(node->left, value, taller);

		if (taller)
		{
			if (node->balance == LH)
			{
				node = this->leftBalance(node, taller);
				taller = false;
			}
			else if (node->balance == EH)
			{
				node->balance = LH;
			}
			else
			{
				node->balance = EH;
				taller = false;
			}
		}
	}
	else
	{
		node->right = this->insertRec(node->right, value, taller);

		if (taller)
		{
			if (node->balance == LH)
			{
				node->balance = EH;
				taller = false;
			}
			else if (node->balance == EH)
			{
				node->balance = RH;
			}
			else
			{
				node = this->rightBalance(node, taller);
				taller = false;
			}
		}
	}

	return node;
}

template <class T>
void AVL<T>::insert(const T &value)
{
	bool taller = true;
	this->root = this->insertRec(this->root, value, taller);
}

template <class T>
Node<T> *AVL<T>::rightBalance(Node<T> *&node, bool &taller)
{
	Node<T> *rightTree = node->right;
	if (rightTree->balance == RH)
	{
		node->balance = EH;
		rightTree->balance = EH;
		node = this->rotateLeft(node);
		taller = false;
	}
	else
	{
		Node<T> *leftTree = rightTree->left;
		if (leftTree->balance == RH)
		{
			node->balance = LH;
			rightTree->balance = EH;
		}
		else if (leftTree->balance == EH)
		{
			node->balance = EH;
			rightTree->balance = EH;
		}
		else
		{
			node->balance = EH;
			rightTree->balance = RH;
		}

		leftTree->balance = EH;
		node->right = this->rotateRight(rightTree);
		node = this->rotateLeft(node);
		taller = false;
	}

	return node;
}

template <class T>
Node<T> *AVL<T>::leftBalance(Node<T> *&node, bool &taller)
{
	Node<T> *leftTree = node->left;
	if (leftTree->balance == LH)
	{
		node->balance = EH;
		leftTree->balance = EH;
		node = this->rotateRight(node);
		taller = false;
	}
	else
	{
		Node<T> *rightTree = leftTree->right;
		if (rightTree->balance == LH)
		{
			node->balance = RH;
			leftTree->balance = EH;
		}
		else if (rightTree->balance == EH)
		{
			node->balance = EH;
			leftTree->balance = EH;
		}
		else
		{
			node->balance = EH;
			leftTree->balance = LH;
		}

		rightTree->balance = EH;
		node->left = this->rotateLeft(leftTree);
		node = this->rotateRight(node);
		taller = false;
	}

	return node;
}

template <class T>
Node<T> *AVL<T>::removeRec(Node<T> *&node, const T &value, bool &shorter, bool &success)
{
	if (node == NULL)
	{
		shorter = false;
		success = false;
		return NULL;
	}

	if (value < node->data) {
		node->left = this->removeRec(node->left, value, shorter, success);

		if (shorter)
			node = removeRightBalance(node, shorter);
	}
	else if (value > node->data) {
		node->right = this->removeRec(node->right, value, shorter, success);

		if (shorter)
			node = removeLeftBalance(node, shorter);
	}
	else {
		Node<T>* removeNode = node;
		if (node->right == NULL) {
			Node<T>* newNode = node->left;
			success = true;
			shorter = true;
			delete removeNode;
			return newNode;
		}
		else if (node->left == NULL) {
			Node<T>* newNode = node->right;
			success = true;
			shorter = true;
			delete removeNode;
			return newNode;
		}
		else {
			Node<T>* exchPtr = node->left;
			while (exchPtr->right != NULL) {
				exchPtr = exchPtr->right;
			}
			node->data = exchPtr->data;
			node->left = this->removeRec(node->left, exchPtr->data, shorter, success);
			if (shorter)
				node = this->removeRightBalance(node, shorter);
		}
	}

	return node;
}

template <class T>
void AVL<T>::remove(const T &value)
{
	bool shorter, success;
	this->root = this->removeRec(this->root, value, shorter, success);
}

template <class T>
Node<T> *AVL<T>::removeRightBalance(Node<T> *&node, bool &shorter)
{
	if (node->balance == LH)
	{
		node->balance = EH;
	}
	else if (node->balance == EH)
	{
		node->balance = RH;
		shorter = false;
	}
	else
	{
		Node<T> *rightTree = node->right;
		if (rightTree->balance == LH)
		{
			Node<T> *leftTree = rightTree->left;
			if (leftTree->balance == LH)
			{
				rightTree->balance = RH;
				node->balance = EH;
			}
			else if (leftTree->balance == EH)
			{
				node->balance = EH;
				rightTree->balance = EH;
			}
			else
			{
				node->balance = LH;
				rightTree->balance = EH;
			}

			leftTree->balance = EH;
			root->right = this->rotateRight(rightTree);
			node = this->rotateLeft(node);
		}
		else
		{
			if (rightTree->balance != EH)
			{
				node->balance = EH;
				rightTree->balance = EH;
			}
			else
			{
				node->balance = RH;
				rightTree->balance = LH;
				shorter = false;
			}

			node = this->rotateLeft(node);
		}
	}

	return node;
}

template <class T>
Node<T> *AVL<T>::removeLeftBalance(Node<T> *&node, bool &shorter)
{
	if (node->balance == RH)
	{
		node->balance = EH;
	}
	else if (node->balance == EH)
	{
		node->balance = LH;
		shorter = false;
	}
	else
	{
		Node<T> *leftTree = node->left;
		if (leftTree->balance == RH)
		{
			Node<T> *rightTree = leftTree->right;
			if (rightTree->balance == RH)
			{
				leftTree->balance = LH;
				node->balance = EH;
			}
			else if (rightTree->balance == EH)
			{
				node->balance = EH;
				leftTree->balance = EH;
			}
			else
			{
				node->balance = RH;
				leftTree->balance = EH;
			}

			rightTree->balance = EH;
			root->left = this->rotateLeft(leftTree);
			node = this->rotateRight(node);
		}
		else
		{
			if (leftTree->balance != EH)
			{
				node->balance = EH;
				leftTree->balance = EH;
			}
			else
			{
				node->balance = LH;
				leftTree->balance = RH;
				shorter = false;
			}

			node = this->rotateRight(node);
		}
	}

	return node;
}

template <class T>
int AVL<T>::getHeightRec(Node<T> *node)
{
	if (node == NULL)
		return 0;
	int lh = this->getHeightRec(node->left);
	int rh = this->getHeightRec(node->right);
	return (lh > rh ? lh : rh) + 1;
}

template <class T>
int AVL<T>::getHeight()
{
	return this->getHeightRec(this->root);
}

template <class T>
void AVL<T>::clearRec(Node<T> *&node)
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
void AVL<T>::clear()
{
	this->clearRec(this->root);
}

template <class T>
void AVL<T>::printTreeStructure()
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