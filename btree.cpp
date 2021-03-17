#include <iostream>
#include "btree.h"
#include <queue>
#include<stack>

using namespace std;


void BTree::insert(int k)
{
	stack <BTreeNode*> S;
	bool inserted = false;
	bool proceed = true;
	 
	if (root == NULL)
	{
		 
		root = new BTreeNode(t, true);
		root->keys[0] = k;  
		root->n = 1;   
	}
	else
	{
		
		if (place(k) == false)
		{
			BTreeNode* p = root;
			int i;

			while (p != nullptr) {
				
				i = p->n - 1;
				while (i >= 0 && p->keys[i] > k)
					i--;
				if (p->keys[i] == k) {
					proceed = false;
					cout << "Kljuc postoji." << endl;
					break;
				}
				else
					p = p->C[i + 1];
			}

			if (proceed == true) {
				
				BTreeNode *s = new BTreeNode(t, false);

				 
				s->C[0] = root;

				
				splitChild(s, root, 0);

				s->insertNonFull(root->keys[root->n - 1]);
				root->n--;

				 
				int i = 0;
				if (s->keys[0] < k)
					i++;
				s->C[i]->insertNonFull(k);

				
				root = s;
			}
		}
		else // If root is not full 
		{
			BTreeNode* p = root;
			int i;

			while (p->leaf != true) {
				S.push(p);
				//find which child should get the key
				i = p->n - 1;
				while (i >= 0 && p->keys[i] > k)
					i--;
				if (p->keys[i] == k) {
					proceed = false;
					cout << "Kljuc postoji." << endl;
					break;
				}
				else
					p = p->C[i + 1];
			}

			//check if the child is full
			if (p->n == 2 * t - 1 && proceed == true) {
				while (inserted != true) {
					BTreeNode* father = S.top();
					S.pop();
					splitChild(father, p, i + 1);

					if (father->n != 2 * t - 1) {
						father->insertNonFull(p->keys[p->n - 1]);
						p->n--;
						inserted = true;

						i = 0;
						while (father->keys[i] < k && i < father->n)
							i++;
						father->C[i]->insertNonFull(k);
					}
					else
						p = father;

				}
			}
			else {
				if (proceed == true)
					p->insertNonFull(k);
			}
		}
	}
}

bool BTree::place(int k) {
	BTreeNode* p = root;
	while (p != nullptr) {
		if (p->n < 2 * t - 1)
			return true;
		else {
			int i = p->n - 1;
			while (i >= 0 && p->keys[i] > k)
				i--;
			p = p->C[i + 1];
		}
	}
	return false;
}

void BTree::splitChild(BTreeNode* father, BTreeNode* split, int i) {
	BTreeNode* child = new BTreeNode(split->t, split->leaf);

	//put values in new node
	int m = split->t;
	for (int j = 0; j < t - 1; j++) {
		child->keys[j] = split->keys[m];
		m++;
		child->n++;
		split->n--;
	}

	if (split->leaf != true) {
		m = split->t;
		for (int j = 0; j < t; j++) {
			child->C[j] = split->C[m];
			split->C[m] = nullptr;
			m++;
		}
	}
	
	for (int j = father->n + 1; j > i + 1; j--)
		father->C[j] = father->C[j - 1];
	father->C[i + 1] = child;
	
}

BTreeNode* BTree::search(int k) 
{
	BTreeNode* p = root;

	while (p->leaf != true) {
		int i = 0;
		while ((i < p->n) && (k > p->keys[i]))
			i++;

		p = p->C[i];
	}

	int i = 0;
	while ((i < p->n) && (k > p->keys[i]))
		i++;

	if (p->keys[i] == k)
		return p;
	else
		return nullptr;
}

void BTree::print2D()
{
	BTreeNode* p = root;
	queue <BTreeNode*> Q;
	int distance = 6;
	const int count = 10;
	int numOfChild;
	int counter = 0;
	bool shouldCount = true;
	int height = 0;
	int numOfKeys = 0;

	Q.push(p);
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		numOfKeys = numOfKeys + p->n;
		if (shouldCount == true) {
			shouldCount = false;
			numOfChild = p->n + 1;
		}
		else
			counter++;

		for (int i = 0; i < distance * count; i++)
			cout << " ";
		cout << "[";
		for (int i = 0; i < p->n; i++)
			if (i != p->n - 1)
				cout << p->keys[i] << ", ";
			else
				cout << p->keys[i];
		cout << "]";
		if (p == root) {
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			distance = distance / 2;
			height++;
		}

		if (counter == numOfChild) {
			counter = 0;
			shouldCount = true;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			distance = distance / 2;
			height++;
		}

		for (int j = 0; j < p->n + 1; j++)
			if (p->C[j] != nullptr)
				Q.push(p->C[j]);
	}
	cout << endl << "Visina stabla je: " << height << endl;
	cout << endl << "Broj kljuceva je: " << numOfKeys << endl;
}

void BTree::deletion(int k) {

	//search for the key
	int i;
	BTreeNode* p = root;
	BTreeNode* father = nullptr;
	stack <BTreeNode*> S;

	while (p->exists(k) == false && p != nullptr) {
		S.push(p);
		i = 0;
		while (i < p->n && p->keys[i] < k)
			i++;
		p = p->C[i];
	}
	if (p == nullptr)
		cout << "Kljuc ne postoji." << endl;
	else
	{
		if (p->leaf == true) {
			//delete right away
			if (p->n > t - 1)
				p->deletefromNode(k);
			else {
				//search for right or left sibling
				bool left = true;
				bool right = true;
				father = S.top();
				S.pop();
				i = 0;
				while (father->C[i] != p)
					i++;

				if (i == 0)
					left = false;
				if (i == father->n)
					right = false;

				if (right == true)
					if (father->C[i + 1]->n <= t - 1)
						right = false;

				if (left == true)
					if (father->C[i - 1]->n <= t - 1)
						left = false;

				if (right == true) {
					BTreeNode* sibling = father->C[i + 1];
					p->deletefromNode(k);

					p->insertNonFull(father->keys[i]);
					father->deletefromNode(father->keys[i]);

					father->insertNonFull(sibling->keys[0]);
					sibling->deletefromNode(sibling->keys[0]);
				}
				else {
					if (left == true) {
						BTreeNode* sibling = father->C[i - 1];
						p->deletefromNode(k);

						p->insertNonFull(father->keys[i - 1]);
						father->deletefromNode(father->keys[i - 1]);

						father->insertNonFull(sibling->keys[sibling->n - 1]);
						sibling->deletefromNode(sibling->keys[sibling->n - 1]);
					}
					else {
						BTreeNode* sibling = nullptr;
						if (i != 0)
							left = true;
						if (i != father->n)
							right = true;

						if (right == true)
							sibling = father->C[i + 1];
						else
							if (left == true) {
								sibling = father->C[i - 1];
								i--;
							}
						p->deletefromNode(k);

						while (p->n < t - 1 && p != root) {
							merge(p, sibling, father, i);
							p = father;
							if (p != root) {
								father = S.top();
								S.pop();
								i = 0;
								while (father->C[i] != p)
									i++;
								if (father->C[i + 1] != nullptr)
									sibling = father->C[i + 1];
								else {
									sibling = father->C[i - 1];
									i--;
								}
							}
						}
					}

				}
			}
		}
		else {
			BTreeNode* internaln = p;
			
			int i = 0;
			while (p->keys[i] != k)
				i++;
			//pred first
			p = p->C[i];
			p = getPred(p);
			BTreeNode* s = internaln->C[i + 1];
			s = getSuc(s);
			if (p->n > t - 1) {
				internaln->insertNonFull(p->keys[p->n - 1]);
				p->deletefromNode(p->keys[p->n - 1]);
				internaln->deletefromNode(k);
			}
			else {
				if (s->n > t - 1) {
					internaln->insertNonFull(s->keys[0]);
					s->deletefromNode(s->keys[0]);
					internaln->deletefromNode(k);
				}
				else {
					i = 0;
					while (internaln->C[i] != p)
						i++;
					merge(p, s, internaln, i);
					p->deletefromNode(k);
				}
			}
		}
	}
}

void BTree::merge(BTreeNode* p, BTreeNode* sibling, BTreeNode* father, int i) {
	for (int j = 0; j < sibling->n; j++)
		p->insertNonFull(sibling->keys[j]);
	p->insertNonFull(father->keys[i]);
	father->deletefromNode(father->keys[i]);

	for (int j = father->n; j > i; j--)
		father->C[j] = father->C[j + 1];
	father->C[father->n + 1] = nullptr;

	if (p->leaf != true) {
		for (int j = p->n - sibling->n, m = 0; j <= p->n; j++, m++)
			p->C[j] = sibling->C[m];
	}
	delete(sibling);

	if (root == father && father->n == 0)
		root = p;
}

BTreeNode* BTree::getSuc(BTreeNode* p) {
	while (p->leaf != true)
		p = p->C[0];
	return p;
}

BTreeNode* BTree::getPred(BTreeNode* p) {
	while (p->leaf != true)
		p = p->C[p->n];
	return p;
}

void BTree::Transform() {
	BTreeNode* p = root;
	queue <BTreeNode*> Q;
	stack <BTreeNode*> S;

	int numOfNode = 0;
	int numOfKeys = 0;

	Q.push(p);
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		numOfNode++;
		numOfKeys = numOfKeys + p->n;
	
		for (int j = 0; j < p->n + 1; j++)
			if (p->C[j] != nullptr)
				Q.push(p->C[j]);
	}

	int midNum = numOfKeys / numOfNode;

	p = root;
	Q.push(p);
	S.push(p);
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();

		for (int j = 0; j < p->n + 1; j++)
			if (p->C[j] != nullptr) {
				Q.push(p->C[j]);
				S.push(p->C[j]);
			}
	}

	while (!S.empty()) {
		p = S.top();
		S.pop();

		int diff = p->n - midNum;
		if (diff < 0)
			get(p, diff);
		if (diff > 0)
			give(p, diff);
	}
}

void BTree::give(BTreeNode* p, int diff) {
	BTreeNode* q = root;
	int i = 0;
	bool father = false;

	for (int j = 0; j < q->n + 1; j++)
		if (q->C[j] == p)
			father = true;

	while (father != true) {
		while (i < q->n && q->keys[i] < p->keys[0])
			i++;
		q = q->C[i];

		for (int j = 0; j < q->n + 1; j++)
			if (q->C[j] == p)
				father = true;
	}

	for (int j = 0; j < diff; i++) {
		q->insertNonFull(p->keys[p->n - 1]);
		p->deletefromNode(p->keys[p->n - 1]);

		int i = 0;
		while (q->C[i] != p)
			i++;
		
		int m = q->n;
		while (i < q->n - 1) {
			i++;
			q->C[m] = q->C[m - 1];
			m--;
		}

	}
}

void BTree::get(BTreeNode* p, int diff) {

}