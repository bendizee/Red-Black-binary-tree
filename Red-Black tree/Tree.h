#pragma once

#include "Node.h"
#include <iomanip>
#include <iostream>
#include <utility>
#include <queue>

template <class T>
class Tree
{
public:

	Tree(); //Сonstructor
	~Tree(); //Destructor

	void insert(T key); //Add node with key
	void remove(T key); //Remove node by key
	Node<T>* search(T key); //Search by key
	void print();
	void detour_straight();
	void detour_symmetric();
	void detour_reverse();
	void detour_width();
	int deep(T key);
	int height();

private:

	void insert_(Node<T>*& root, Node<T>* node);
	void insertBalance(Node<T>*& root, Node<T>* node);

	void remove_(Node<T>*& root, Node<T>* node);
	void removeBalanced(Node<T>*& root, Node<T>* node, Node<T>* parent);
	void destroy(Node<T>*& node);

	Node<T>* search_(Node<T>* node, T key)const;
	void print_(Node<T>* node)const;

	void leftRotate(Node<T>*& root, Node<T>* x); //Left turn
	void rightRotate(Node<T>*& root, Node<T>* y); //Right turn

	//Detours
	//Depth
	void detour_straight_(Node<T>* tree)const; //Pre-order
	void detour_symmetric_(Node<T>* tree)const; //In-order
	void detour_reverse_(Node<T>* tree)const; //Post order

	//Width
	void detour_width_(Node<T>* tree)const;

	int deep_(Node<T>* node, T key,int d);
	int height_(Node<T>* node);
	int max(int a, int b);

	Node<T>* root;
};

template <class T>
Tree<T>::Tree() : root(NULL)
{
	root = nullptr;
};

template <class T>
Tree<T>::~Tree() {
	destroy(root);
};

template <class T>
void Tree<T>::leftRotate(Node<T>*& root, Node<T>* x)
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
void Tree<T>::rightRotate(Node<T>*& root, Node<T>* y)
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

template <class T>
void Tree<T>::insert(T key)
{
	Node<T>* z = new Node<T>(key, red, NULL, NULL, NULL);
	insert_(root, z);
};

template <class T>
void Tree<T>::insert_(Node<T>*& root, Node<T>* node)
{
	Node<T>* x = root;
	Node<T>* y = NULL;

	while (x != NULL)
	{
		y = x;
		if (node->key > x->key)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else
		root = node;
	node->color = red;
	insertBalance(root, node);
};

template<class T>
void Tree<T>::insertBalance(Node<T>*& root, Node<T>* node)
{
	Node<T>* parent;
	parent = node->parent;
	while (node != Tree::root && parent->color == red)
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
					leftRotate(root, parent);
					std::swap(node, parent);
				}
				rightRotate(root, gparent);
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
					rightRotate(root, parent);
					std::swap(node, parent);
				}
				leftRotate(root, gparent);
				parent->color = black;
				gparent->color = red;
				break;
			}
		}
	}
	root->color = black;
};

template<class T>
void Tree<T>::remove(T key)
{
	Node<T>* deletenode = search_(root, key);
	if (deletenode != NULL)
		remove_(root, deletenode);
}

template<class T>
void Tree<T>::remove_(Node<T>*& root, Node<T>* node)
{
	Node<T>* child, * parent;
	NodeColor color;
	if (node->left != NULL && node->right != NULL)
	{
		Node<T>* replace = node;
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
			{
				node->parent->left = replace;
			}
			else
			{
				node->parent->right = replace;
			}
		}
		else
		{
			root = replace;
		}
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			if (child != NULL)
			{
				child->parent = parent;
			}
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == black)
		{
			removeBalanced(root, child, parent);
		}

		delete node;
		return;
	}
	if (node->left != NULL)
	{
		child = node->left;
	}
	else
	{
		child = node->right;
	}

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	if (parent)
	{
		if (node == parent->left)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
	}
	else
	{
		Tree::root = child;
	}

	if (color == black)
	{
		removeBalanced(root, child, parent);
	}
	delete node;

}

template<class T>
void Tree<T>::removeBalanced(Node<T>*& root, Node<T>* node, Node<T>* parent)
{
	Node<T>* othernode;
	while ((!node) || node->color == black && node != Tree::root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == red)
			{
				othernode->color = black;
				parent->color = red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == black)
				{
					othernode->left->color = black;
					othernode->color = red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = black;
				othernode->right->color = black;
				leftRotate(root, parent);
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
				rightRotate(root, parent);
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
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = black;
				othernode->left->color = black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = black;
}

template<class T>
Node<T>* Tree<T>::search(T key)
{
	return search_(root, key);
}

template<class T>
Node<T>* Tree<T>::search_(Node<T>* node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
		{
			return search_(node->right, key);
		}
		else
		{
			return search_(node->left, key);
		}
}

template <class T>
void Tree<T>::destroy(Node<T>*& node)
{
	if (node == NULL)
	{
		return;
	}
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = NULL;
}

template<class T>
void Tree<T>::print() {
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		print_(root);
	}
}

template<class T>
void Tree<T>::print_(Node<T>* node)const {
	if (node == NULL)
	{
		return;
	}
	if (node->parent == NULL)
	{
		std::cout << node->key << "(" << node->color << ") is root" << std::endl;
	}
	else if (node->parent->left == node)
	{
		std::cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "left child" << std::endl;
	}
	else
	{
		std::cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "right child" << std::endl;
	}
	print_(node->left);
	print_(node->right);
}

template<class T>
void Tree<T>::detour_straight() 
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detour_straight_(root);
	}
};

template<class T>
void Tree<T>::detour_straight_(Node<T>* tree)const 
{
	if (tree != NULL) 
	{
		std::cout << tree->key << " ";
		detour_straight_(tree->left);
		detour_straight_(tree->right);
	}
}

template <class T>
void Tree<T>::detour_symmetric()
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detour_symmetric_(root);
	}
};

template <class T>
void Tree<T>::detour_symmetric_(Node<T>* tree)const
{
	if (tree != NULL) 
	{
		detour_symmetric_(tree->left);
		std::cout << tree->key << " ";
		detour_symmetric_(tree->right);
	}
}

template <class T>
void Tree<T>::detour_reverse()
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detour_reverse_(root);
	}
};

template <class T>
void Tree<T>::detour_reverse_(Node<T>* tree)const
{
	if (tree != NULL) 
	{
		detour_reverse(tree->left);
		detour_reverse(tree->right);
		std::cout << tree->key << " ";
	}
}

template <class T>
void Tree<T>::detour_width()
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detour_width_(root);
	}
};

template <class T>
void Tree<T>::detour_width_(Node<T>* tree)const
{
	if (tree != NULL)
	{
		std::queue <Node<T>*> q;
		q.push(tree);
		while(!q.empty())
		{
			std::cout << q.front()->key << ' ';
			if (q.front()->left != NULL)
			{
				q.push(q.front()->left);
			}
			if (q.front()->right != NULL)
			{
				q.push(q.front()->right);
			}
			q.pop();
		}
	}
}

template <class T>
int Tree<T>::deep(T key)
{
	int d = deep_(root, key, 0);
	return d;
};

template <class T>
int Tree<T>::deep_(Node<T>* node, T key, int d)
{
	if (node == NULL || node->key == key)
		return d;
	else
		if (key > node->key)
		{
			d++;
			return deep_(node->right, key, d);
		}
		else
		{
			d++;
			return deep_(node->left, key, d);
		}
	return d;
}

template <class T>
int Tree<T>::height()
{
	return height_(root);
};

template <class T>
int Tree<T>::height_(Node<T>* tree)
{
	if (tree == NULL)
	{
		return 0;
	}

	return 1 + max(height_(tree->left), height_(tree->right));
}

template <class T>
int Tree<T>::max(int a, int b) 
{
	return a > b ? a : b;
}