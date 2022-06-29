#include "Node.h"
#include <cstddef>

template <class T>
class Searcher
{
    public:
    Node<T>* search(Node<T>* node, T key)const;
};

template<class T>
Node<T>* Searcher<T>::search(Node<T>* node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
		{
			return search(node->right, key);
		}
		else
		{
			return search(node->left, key);
		}
}