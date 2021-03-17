#include <iostream>

#include "asf.h"
using namespace std;

 
BTreeNode::BTreeNode(int t1, bool leaf1)
{
	
	t = t1;
	leaf = leaf1;

	
	keys = new int[2 * t - 1];
	C = new BTreeNode* [2 * t];
	for (int i = 0; i < 2 * t; i++) {
		C[i] = nullptr;
	}
	
	n = 0;
}

void BTreeNode::insertNonFull(int k)
{
	bool proceed = exists(k);

	if (proceed == false) {
		int i = n - 1;

		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = k;
		n = n + 1;
	}
	else
		std::cout << "Kljuc postoji." << std::endl;
}

void BTreeNode::deletefromNode(int k) 
{
	bool proceed = exists(k);

	if (proceed = true) {
		int i = 0;

		while (i < n && keys[i] < k)
			i++;

		while (i < n) {
			keys[i] = keys[i + 1];
			i++;
		}

		n = n - 1;
	}
	else
		std::cout << "Kljuc ne postoji." << std::endl;
}

bool BTreeNode::exists(int k) {
	if (this != nullptr) {
		for (int i = 0; i < n; i++)
			if (keys[i] == k)
				return true;
	}
	return false;
}