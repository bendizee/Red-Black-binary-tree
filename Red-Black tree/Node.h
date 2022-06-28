#pragma once
enum NodeColor {black, red};

template <class TypeKey>
struct Node 
{
	TypeKey key;
	NodeColor color; //Color of node
	Node <TypeKey>* left;
	Node <TypeKey>* right; 
	Node <TypeKey>* parent;

	Node(TypeKey k, NodeColor c, Node* p, Node* l, Node* r) :
		key(k), color(c), parent(p), left(l), right(r) { };
};
