#include"Tree.h"
#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100 };
	Tree<int> tree;
	for (auto num : nums)
	{
		tree.insert(num);
	}
	cout << "30:";
	cout << endl << tree.search(30)->key << endl;
	cout << " 100";
	tree.remove(100);
	cout << endl;
	cout << ":\n";
	tree.detour_width();
	cout << endl;
	cout << " 50:\n" << tree.deep(50) << endl;
	cout << ":\n" << tree.height() << endl;
	cout << ":\n";
	cout << endl;
	tree.print();
	cin.get();
	return 0;
}