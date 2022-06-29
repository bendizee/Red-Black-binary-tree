#include "Node.h"
#include <queue>
#include <iostream>

template <class T>
class Detourer
{
    public:
    //Depth
	void detour_straight(Node<T>* tree)const; //Pre-order
	void detour_symmetric(Node<T>* tree)const; //In-order
	void detour_reverse(Node<T>* tree)const; //Post order
    //Width
	void detour_width(Node<T>* tree)const;
};

template<class T>
void Detourer<T>::detour_straight(Node<T>* tree)const 
{
	if (tree != NULL) 
	{
		std::cout << tree->key << " ";
		detour_straight(tree->left);
		detour_straight(tree->right);
	}
}

template <class T>
void Detourer<T>::detour_symmetric(Node<T>* tree)const
{
	if (tree != NULL) 
	{
		detour_symmetric(tree->left);
		std::cout << tree->key << " ";
		detour_symmetric(tree->right);
	}
}

template <class T>
void Detourer<T>::detour_reverse(Node<T>* tree)const
{
	if (tree != NULL) 
	{
		detour_reverse(tree->left);
		detour_reverse(tree->right);
		std::cout << tree->key << " ";
	}
}

template <class T>
void Detourer<T>::detour_width(Node<T>* tree)const
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

