#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
private:
	T data;
	Node<T>* left;
	Node<T>* right;
public:
	Node();
	Node(T newData, Node<T> *newLeft = NULL, Node<T> *newRight = NULL);

	void setData(T newData);
	void setLeft(Node<T> *newLeft);
	void setRight(Node<T> * newRight);

	T getItem() const;
	Node<T>* getLeft() const;
	Node<T>* getRight() const;
};


													//CONSTRUCTOR
template <typename T>
Node<T>::Node() :data(), left(NULL), right(NULL)
{}



													//CONSTRUCTOR (OVERLOADED)
template <typename T>
Node<T>::Node(T newData, Node<T>* newLeft, Node<T>* newRight)
{
	data = newData;
	left = NULL;
	right = NULL;
}


													//SETDATA
template <typename T>
void Node<T>::setData(T newData)
{
	data = newData;
}


													//SETLEFT
template <typename T>
void Node<T>::setLeft(Node<T>* newLeft)
{
	left = newLeft;
}


													//SETRIGHT
template <typename T>
void Node<T>::setRight(Node<T>* newRight)
{
	right = newRight;
}


													//GETDATA
template <typename T>
T Node<T>::getItem() const
{
	return data;
}


													//GETLEFT
template <typename T>
Node<T>* Node<T>::getLeft() const
{
	return left;
}


													//GETRIGHT
template <typename T>
Node<T>* Node<T>::getRight() const
{
	return right;
}


#endif