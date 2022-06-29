#pragma once

#include "Node.h"
#include "Balancer.h"
#include "Searcher.h"
#include "Detourer.h"
#include <iomanip>
#include <iostream>
#include <utility>

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

	Detourer<T> detourer;
    Balancer<T> balance;
    Searcher<T> searcher;

private:

	void insert_(Node<T>*& root, Node<T>* node);

	void remove_(Node<T>*& root, Node<T>* node);
	void destroy(Node<T>*& node);

	void print_(Node<T>* node)const;

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
	balance.insertBalanced(root, node);
};

template<class T>
void Tree<T>::remove(T key)
{
	Node<T>* deletenode = searcher.search(root, key);
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
			balance.removeBalanced(root, child, parent);
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
		balance.removeBalanced(root, child, parent);
	}
	delete node;

}



template<class T>
Node<T>* Tree<T>::search(T key)
{
	return searcher.search(root, key);
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
		detourer.detour_straight(root);
	}
};

template <class T>
void Tree<T>::detour_symmetric()
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detourer.detour_symmetric(root);
	}
};

template <class T>
void Tree<T>::detour_reverse()
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detourer.detour_reverse(root);
	}
};

template <class T>
void Tree<T>::detour_width()
{
	if (root == NULL)
	{
		std::cout << "empty tree\n";
	}
	else
	{
		detourer.detour_width(root);
	}
};

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