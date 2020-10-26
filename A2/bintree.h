#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>

#include <fstream>
#include "nodedata.h"

using namespace std;

class BinTree {				// you add class/method comments and assumptions
	friend ostream& operator<<(ostream& outputStream, const BinTree& tree); // overloaded operator
																			// to return output data

public:
	BinTree();								// constructor
	BinTree(const BinTree&);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	

	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true

	BinTree& operator=(const BinTree&);     // Creates deep copy of right BinTree and assigns to left side
	bool operator==(const BinTree&) const;  // checks to see if two BinTree objects are equal
	bool operator!=(const BinTree&) const;	// checks to see if two BinTree objects are not equal
				
	bool insert(NodeData*);					// inserts NodeData value into BST
	bool retrieve(const NodeData& target, NodeData*& holder);	// checks to see if NodeData value exists
	int getHeight(const NodeData&) const;	// returns height of tree at given root

	void bstreeToArray(NodeData* []);		// converts BST into array
	void arrayToBSTree(NodeData* []);		// converts array into BST
	void displaySideways() const;			// provided below, displays the tree sideways

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

// utility functions
	void inorderHelper(Node*) const;			// helper for operator<< overload
	void sideways(Node*, int) const;			// helper for displaySideways()
	void makeEmptyHelper(Node*& cur);			// helper for makeEmpty
	void assignHelper(Node* lhs, Node*& rhs);	// helper for operator= 
	bool equalCompareHelper(Node* ls, Node* rs) const;  // helper for operator== 
	bool insertHelper(Node*& cur, NodeData* data);      // helper for insert
	bool retrieveHelper(Node*& cur, const NodeData& target, NodeData*& holder) const; // helper for retrieve
	int getHeightHelper(const NodeData& target, Node* cur) const; // helper for getHeight
	int getHeightOtherHelper(Node* cur) const; // helper for getHeightHelper
	void arrayToBSTreeHelper(Node* cur, NodeData* arr[], int left, int right); // helper for arrayToBSTree
	int bstreeToArrayHelper(Node* cur, NodeData* arr[]); // helper for bstreeToArray
};
#endif