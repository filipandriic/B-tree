#pragma once
// A BTree node 
class BTreeNode
{
	int *keys;  // An array of keys 
	int t;      // Minimum degree (defines the range for number of keys) 
	BTreeNode **C; // An array of child pointers 
	int n;     // Current number of keys 
	bool leaf; // Is true when node is leaf. Otherwise false 
public:
	BTreeNode(int _t, bool _leaf); 

	void insertNonFull(int k);

	void deletefromNode(int k);

	bool exists(int k);

	friend class BTree;
}; 
