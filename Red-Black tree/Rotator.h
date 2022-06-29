#include "Node.h"
#include <cstddef>

template <class T>
class Rotator
{
    public:
    void leftRotate(Node<T>*& root, Node<T>* x); //Left turn
	void rightRotate(Node<T>*& root, Node<T>* y); //Right turn
};

template <class T>
void Rotator<T>::leftRotate(Node<T>*& root, Node<T>* x)
{
	Node<T>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL)
	{
		root = y;
	}
	else {
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
};

template <class T>
void Rotator<T>::rightRotate(Node<T>*& root, Node<T>* y)
{
	Node<T>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
	{
		x->right->parent = y;
	}

	x->parent = y->parent;
	if (y->parent == NULL)
	{
		root = x;
	}	
	else {
		if (y == y->parent->right)
		{
			y->parent->right = x;
		}
		else
		{
			y->parent->left = x;
		}
	}
	x->right = y;
	y->parent = x;
};