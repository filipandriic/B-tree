#pragma once
#include "asf.h"
// A BTree 
class BTree
{
	BTreeNode *root; 
	int t;
public:
	
	BTree(int _t)
	{
		root = nullptr;  t = _t;
	}

	
	BTreeNode* search(int k);

	
	void insert(int k);

	void splitChild(BTreeNode* father, BTreeNode* split, int i);

	bool place(int k);

	void print2D();
	
	void deletion(int k);

	void merge(BTreeNode* p, BTreeNode* sibling, BTreeNode* father, int i);

	BTreeNode* getSuc(BTreeNode* p);

	BTreeNode* getPred(BTreeNode* p);

	void Transform();

	void give(BTreeNode* p, int diff);

	void get(BTreeNode* p, int diff);

	friend class BTreeNode;
};
