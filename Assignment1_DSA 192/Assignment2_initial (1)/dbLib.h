#include "main.h"

template <typename T>
class Link
{
public:
    T data;
    Link<T> *next;
    Link<T>(const Link<T> &n = nullptr) { next = n; }
    Link<T>(const T &ele, const Link<T> &n = nullptr)
    {
        data = ele;
        next = n;
    }
};
template <typename T>
class List
{
    // Return: The number of elements in the list.
    virtual int length() const = 0;
    virtual void insert(const T &ele) = 0;
};
template <typename T>
class LList : public List<T>
{
private:
    Link<T> *head;
    Link<T> *last;
    Link<T> *curr;
    int cnt;

public:
    LList() { head = last = curr = new Link<T>(); }
    int length() const { return cnt; }
    void insert(const T &ele)
    {
        curr->next = new Link<T>(ele, curr->next);
    }
};

template <typename T>
class Node
{
public:
    T data;
    Node<T> *left;
    Node<T> *right;

    Node<T>(const Node<T> &left = nullptr, const Node<T> &right = nullptr)
    {
        this->left = left;
        this->right = right;
    }

    Node<T>(const T &ele, const Node<T> &left = nullptr, const Node<T> &right = nullptr)
    {
        data = ele;
        this->left = left;
        this->right = right;
    }
};

template <typename T>
class BinaryTree
{
    virtual int getHeight() const = 0;
    virtual void insert(const T &ele) = 0;
};

template <typename T>
class AVLTree
{
private:
    Node<T> *root;
    int height;

public:
    AVLTree()
    {
        this->root = nullptr;
    }

    int getHeight() const { return this->height; }
    void insert(const T &ele)
    {
    }
};