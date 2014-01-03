#ifndef BST_H
#define BST_H

#include "Node.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using std::ostream;
using std::endl;
using std::cout;
using std::setw;


template <typename T>
class BST
{
private:
	enum direction { left, right, none };
	Node<T>* root;
	int numNodes;

	T findHelper(T key, Node<T>* node) const;	
	Node<T>* copyHelper(Node<T>* node, Node<T>* other);	
	void displayHelper(ostream& out, Node<T>* node, int level, direction d) const;	
	int levelHelper(Node<T>* node) const;	
	Node<T>* insertHelper(T data, Node<T>* node);	
	void destructorHelper(Node<T>* node);	
	Node<T>* removeHelper(T key, Node<T>* node, T& removed);
	Node<T>* removeNode(Node<T>* node);
	void goGetData(Node<T>* node);
	void inorderDisplayHelper(ostream& out, Node<T>* node) const;

	int max(int a, int b) const; 

public:
	BST();	
	BST(const BST& rhs);	
	const BST& operator=(const BST& rhs);
	~BST();	

	void insert(T data); 
	T find(T key) const;	
	T remove(T key);
	void display(ostream& out) const;	
	void inorderDisplay(ostream& out) const;
	int count() const;	
};



//REMOVEHELPER
template <typename T>
Node<T>* BST<T>::removeHelper(T key, Node<T>* node, T& removed)
{
	if (node != NULL)
	{
		if (node->getItem() == key)	//found data
		{
			removed = node->getItem();
			node = removeNode(node);
		}
		else if (node->getItem() > key)
		{
			node->setLeft(removeHelper(key, node->getLeft(), removed));
		}
		else
		{
			node->setRight(removeHelper(key, node->getRight(), removed));
		}
	}

	return node;
}



//REMOVENODE
template <typename T>
Node<T>* BST<T>::removeNode(Node<T>* node)
{
	if (node->getLeft() == NULL && node->getRight() == NULL)
	{
		delete node;
		node = NULL;
	}
	else if (node->getLeft() == NULL)	//implied that right is not null
	{
		Node<T>* temp = node;
		node = node->getRight();
		delete temp;
	}
	else if (node->getRight() == NULL)	//implies that left is not null
	{
		Node<T>* temp = node;
		node = node->getLeft();
		delete temp;
	}
	else
	{
		goGetData(node);
	}

	return node;
}


//FINDHELPER
template <typename T>
T BST<T>::findHelper(T key, Node<T>* node) const
{
	T data = T();
	if (node != NULL)
	{
		if (node->getItem() == key)
		{
			data = node->getItem();
		}
		else if (node->getItem() > key)
		{
			return findHelper(key, node->getLeft());
		}
		else
		{
			return findHelper(key, node->getRight());
		}
	}

	return data;
}


//COPYHELPER
template <typename T>
Node<T>* BST<T>::copyHelper(Node<T>* node, Node<T>* other)
{
	if (other != NULL)
	{
		node = new Node<T>(other->getItem());
		node->setLeft(copyHelper(node->getLeft(), other->getLeft()));
		node->setRight(copyHelper(node->getRight(), other->getRight()));
	}
	else 
	{
		node = NULL;
	}

	return node;
}



//DISPLAYHELPER
template <typename T>
void BST<T>::displayHelper(ostream& out, Node<T>* node, int level, direction d) const
{
	if (node != NULL)
	{
		displayHelper(out, node->getLeft(), level-1, left);
		out << endl;
		out << setw(5 * level) << node->getItem();

		if (d == right)
			out << "/" << endl;
		else if (d == left)
			out << "\\" << endl;
		else
			out << "-" << endl;
		out << endl;
		displayHelper(out, node->getRight(), level-1, right);
	}
}


//LEVELHELPER
template <typename T>
int BST<T>::levelHelper(Node<T>* node) const
{
	int level = 1;

	if (node->getLeft() != NULL)
	{
		level = max(level, 1+levelHelper(node->getLeft()));
	}

	if (node->getRight() != NULL)
	{
		level = max(level, 1+levelHelper(node->getRight()));
	}

	return level;
}



//INSERTHELPER
template <typename T>
Node<T>* BST<T>::insertHelper(T data, Node<T>* node)
{
	Node<T>* temp = node;
	if (node == NULL)
	{
		temp = new Node<T>(data);
	}

	else if (node->getItem() > data)
	{
		node->setLeft(insertHelper(data, node->getLeft()));
	}
	else
	{
		node->setRight(insertHelper(data, node->getRight()));
	}

	return temp;
}



//MAX
template <typename T>
int BST<T>::max(int a, int b) const
{
	if (a > b) return a;
	else return b;
}



//GOGETDATA
template <typename T>
void BST<T>::goGetData(Node<T>* node)
{
	Node<T>* right = node->getRight();
	Node<T>* prev = NULL;
	while (right->getLeft() != NULL)
	{
		prev = right;
		right = right->getLeft();
	}
	node->setData(right->getItem());
	if (prev == NULL)
	{
		node->setRight(right->getRight());
	}
	else
	{
		prev->setLeft(right->getRight());
	}

	delete right;
}



//CONSTRUCTOR
template <typename T>
BST<T>::BST()
{
	root = NULL;
	numNodes = 0;
}



//COPY CONSTRUCTOR
template <typename T>
BST<T>::BST(const BST &rhs)
{
	this->numNodes = rhs.numNodes;
	root = NULL;
	root = copyHelper(root, rhs.root);
}


//OPERATOR =
template <typename T>
const BST<T>& BST<T>::operator=(const BST<T> &bst)
{
	if (this != &bst)
	{
		destructorHelper(root);
		numNodes = bst.numNodes;
		root = copyHelper(root, bst.root);
	}

	return *this;
}



template <typename T>
void BST<T>::destructorHelper(Node<T>* node)
{
	if (node != NULL)
	{
		destructorHelper(node->getLeft());
		destructorHelper(node->getRight());
		delete node;
		numNodes--;
	}
}



//DESTRUCTOR
template <typename T>
BST<T>::~BST()
{
	destructorHelper(root);
	root = NULL;
}



//INSERT
template <typename T>
void BST<T>::insert(T data)
{
	if (find(data) == "")
	{
		root = insertHelper(data, root);
		numNodes++;
	}
	/*root = insertHelper(data, root);
	numNodes++;*/
}


//DISPLAY
template <typename T>
void BST<T>::display(ostream& out) const
{
	int level = levelHelper(root);	//determines how tall tree is
	displayHelper(out, root, level, none);
}


//FIND
template <typename T>
T BST<T>::find(T key) const
{
	return findHelper(key, root);
}



//REMOVE
template <typename T>
T BST<T>::remove(T key)
{
	T removed = T();
	root = removeHelper(key, root, removed);
	numNodes--;
	return removed;
}



//SIZE
template <typename T>
int BST<T>::count() const
{
	return numNodes;
}



template <typename T>
void BST<T>::inorderDisplay(ostream& out) const
{
	inorderDisplayHelper(out, root);
}


template <typename T>
void BST<T>::inorderDisplayHelper(ostream& out, Node<T>* node) const
{
	if (node->getLeft() != NULL)
	{
		inorderDisplayHelper(out, node->getLeft());
		//out << node->getLeft()->getItem() << endl;
	}
	out << node->getItem() << endl;
	if (node->getRight() != NULL)
	{
		inorderDisplayHelper(out, node->getRight());
		//out << node->getRight()->getItem() << endl;
	}
}


#endif