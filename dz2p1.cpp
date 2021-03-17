#include <iostream> 
#include "btree.h"
using namespace std;

int main()
{
	int t;
	cout << "Stable degree? ";
	cin >> t;
	BTree tree(t/2);
	int choice;
	while (true) {
		cout << "\n--------MENU-------\n"
			"1. Insert in tree.\n"
			"2. Print the tree.\n"
			"3. Search for the number.\n"
			"4. Delete from tree.\n"
			"0. End the program.\n" << endl;
		cout << "Your choice? ";
		cin >> choice;
		switch (choice) {
		case 1:
			int key;
			cout << "Which number? ";
			cin >> key;
			tree.insert(key);
			break;

		case 2:
			tree.print2D();
			break;

		case 3:
			cout << "Which number? ";
			cin >> key;
			(tree.search(key) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";
			break;

		case 4:
			cout << "Which number? ";
			cin >> key;
			tree.deletion(key);
			break;

		case 0:
			cout << "Goodbye!" << endl;
			exit(0);
		}
	}
	return 0;
}