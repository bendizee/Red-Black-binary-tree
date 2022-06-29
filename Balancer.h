#include "Node.h"
#include "Tree.h"
#include "Rotator.h"
#include <iomanip>
#include <utility>

template <class T>
class Balancer
{
    public:
    Rotator<T> rotate;

	void insertBalanced(Node<T>*& root, Node<T>* node);
    void removeBalanced(Node<T>*& root, Node<T>* node, Node<T>* parent);
};

template<class T>
void Balancer<T>::insertBalanced(Node<T>*& root, Node<T>* node)
{
	Node<T>* parent;
	parent = node->parent;
	while (node != root && parent->color == red)
	{
		Node<T>* gparent = parent->parent;
		if (gparent->left == parent)
		{
			Node<T>* uncle = gparent->right;
			if (uncle != NULL && uncle->color == red)
			{
				parent->color = black;
				uncle->color = black;
				gparent->color = red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					rotate.leftRotate(root, parent);
					std::swap(node, parent);
				}
				rotate.rightRotate(root, gparent);
				gparent->color = red;
				parent->color = black;
				break;
			}
		}
		else
		{
			Node<T>* uncle = gparent->left;
			if (uncle != NULL && uncle->color == red)
			{
				gparent->color = red;
				parent->color = black;
				uncle->color = black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rotate.rightRotate(root, parent);
					std::swap(node, parent);
				}
				rotate.leftRotate(root, gparent);
				parent->color = black;
				gparent->color = red;
				break;
			}
		}
	}
	root->color = black;
};

template<class T>
void Balancer<T>::removeBalanced(Node<T>*& root, Node<T>* node, Node<T>* parent)
{
	Node<T>* othernode;
	while ((!node) || node->color == black && node != root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == red)
			{
				othernode->color = black;
				parent->color = red;
				rotate.leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == black)
				{
					othernode->left->color = black;
					othernode->color = red;
					rotate.rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = black;
				othernode->right->color = black;
				rotate.leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == red)
			{
				othernode->color = black;
				parent->color = red;
				rotate.rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == black) && (!othernode->right || othernode->right->color == black))
			{
				othernode->color = red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == black)
				{
					othernode->right->color = black;
					othernode->color = red;
					rotate.leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = black;
				othernode->left->color = black;
				rotate.rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = black;
};