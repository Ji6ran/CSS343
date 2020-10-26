#include "bintree.h"
#include <algorithm>
using namespace std;

//--------------------------- operator<< ------------------------------------
// Displays data from BST in order
// Uses helper function inOrderHelper
// Preconditions: NONE
// Postconditions: Prints output data of BST
// --------------------------------------------------------------------------
ostream& operator<<(ostream& outputStream, const BinTree& tree) {
	tree.inorderHelper(tree.root);
	outputStream << endl;
	return outputStream;
}

//--------------------------- inorderHelper ---------------------------------
// Helper function for operator<<
// --------------------------------------------------------------------------
void BinTree::inorderHelper(Node* cur) const {
	if (cur != nullptr) {
		inorderHelper(cur->left);
		cout << *cur->data << " ";
		inorderHelper(cur->right);
	}
}

//------------------------- Default Constructor -----------------------------
// Creates empty BST with root = nullptr
// Preconditions: NONE
// Postconditions: BST is created
// --------------------------------------------------------------------------
BinTree::BinTree() { this->root = nullptr; }

//-------------------------- Copy Constructor -------------------------------
// Creates deep copy of referenced BST
// const passed in parameter so only BST is passed in
// Preconditions: NONE
// Postconditions: Left tree becomes deep copy of right tree (source)
// --------------------------------------------------------------------------
BinTree::BinTree(const BinTree& source) { this->root = nullptr; *this = source; }

//----------------------------- Destructor ----------------------------------
// Uses makeEmpty function to destruct
// Preconditions: NONE
// Postconditions: BST is deleted
// --------------------------------------------------------------------------
BinTree::~BinTree() {
	this->makeEmpty();
}

//------------------------------ isEmpty ------------------------------------
// Checks if BST is empty
// Preconditions: NONE
// Postconditions: BST remains unchanged
// --------------------------------------------------------------------------
bool BinTree::isEmpty() const {
	if (this->root == nullptr) return true;
	else return false;
}

//----------------------------- makeEmpty -----------------------------------
// Deletes entire BST
// Uses helper function makeEmptyHelper
// Used in destructor
// Preconditions: NONE
// Postconditions: BST is deleted
// --------------------------------------------------------------------------
void BinTree::makeEmpty() {
	makeEmptyHelper(this->root);
}
//------------------------- makeEmptyHelper ---------------------------------
// Helper function for makeEmpty
// --------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node*& cur) {
	if (cur != nullptr) {
		makeEmptyHelper(cur->left); // go left
		makeEmptyHelper(cur->right); // go right

		if (cur->data != nullptr) {
			delete cur->data; // delete then set to null to avoid mem leak
			cur->data = nullptr;
		}
		delete cur;
		cur = nullptr;
	}
}

//---------------------------- operator= ------------------------------------
// Left tree is assigned properties of right tree
// Uses helper function assignHelper
// Preconditions: Both left and right must be BSTs
// Postconditions: Left tree becomes deep copy of right tree
// --------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& rTree)
{
	if (*this == rTree) return *this;
	this->makeEmpty();  // deletes the left tree
	assignHelper(rTree.root, this->root);
	return *this;   // returns lTree when its the same as rTree
}

// ------------------------- assignHelper -----------------------------------
// Helper function to overloaded assignment operator
// --------------------------------------------------------------------------
void BinTree::assignHelper(Node* rs, Node*& ls)
{
	if (rs == nullptr) ls = nullptr;
	else {
		delete ls; 
		ls = new Node();
		NodeData* temp = new NodeData(*rs->data); // create temp nodedata and assign its data to left side
		ls->data = temp;
		assignHelper(rs->left, ls->left);  // go left
		assignHelper(rs->right, ls->right); // go right
	}
}

//---------------------------- operator== -----------------------------------
// Uses helper function equalCompareHelper
// Checks if two BST are the same
// Preconditions: NONE
// Postconditions: BST remains unchanged
// --------------------------------------------------------------------------
bool BinTree::operator==(const BinTree& source) const {
	return equalCompareHelper(this->root, source.root);
}

//------------------------- equalCompareHelper ------------------------------
// Helper function for operator== overloading
// --------------------------------------------------------------------------
bool BinTree::equalCompareHelper(Node* ls, Node* rs) const {
	if (ls == nullptr && rs == nullptr) return true;
	if (ls == nullptr || rs == nullptr) return false;
	if (*ls->data != *rs->data) return false;
	return equalCompareHelper(ls->left, rs->left) && equalCompareHelper(ls->right, rs->right);
	// compare left side of both trees and right side of both trees
}

//---------------------------- operator!= -----------------------------------
// Checks if two BinTrees are not the same
// Preconditions: NONE
// Postconditions: BST remains unchanged
// --------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree& source) const {
	return !(*this == source);
}

//------------------------------ insert -------------------------------------
// Inserts new node into BST holding NodeData
// Uses helper function insertHelper
// Preconditions: NONE
// Postconditions: New Node inserted into BST
// --------------------------------------------------------------------------
bool BinTree::insert(NodeData* data) {
	return insertHelper(this->root, data);
}

//----------------------------- insertHelper --------------------------------
// Helper function for insert
// If NodeData is in BSTree, it will not be inserted
// --------------------------------------------------------------------------
bool BinTree::insertHelper(Node*& cur, NodeData* data) {
	if (cur == nullptr) { // if node is null
		delete cur; // delete cur
		cur = new Node(); // create a new instance of a node and initialize its data as NodeData being passed in
		cur->data = data; // assign data to cur->data
		cur->left = nullptr; // then set left and right to null
		cur->right = nullptr;
		return true; // return true if insert worked
	}
	else if (*data < *cur->data) { // if node exists and data being passed in is less than cur node's data
		insertHelper(cur->left, data); // recursively call to go left until it's null so you can insert
	}
	else if (*data > *cur->data) { // same as above but if it's greater than
		insertHelper(cur->right, data);
	}
	else return false; // if nothing works return false as value could not be inserted

}

//------------------------------- retrieve ----------------------------------
// Checks if NodeData is in BST
// If it exists, pointer to node is returned
// Uses helper function retrieveHelper
// Preconditions: NONE
// Postconditions: BST remains unchanged
// --------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData& target, NodeData*& holder) {
	retrieveHelper(this->root, target, holder); 
	if (holder != nullptr) return true;
	else return false;
}

//---------------------------- retrieveHelper -------------------------------
// Helper function for retrieve
// --------------------------------------------------------------------------
bool BinTree::retrieveHelper(Node*& cur, const NodeData& target, NodeData*& holder) const {
	if (cur == nullptr) { // if cur is null, set holder to null and return false (no data found)
		holder = nullptr;
		return false;
	}
	if (*cur->data == target) { // if it's found, set it = to holder and then return true
						// which will then be stored in main retrieve func
		holder = cur->data;
		return true;
	}
	if (*cur->data < target) retrieveHelper(cur->right, target, holder); // if data is less than target, go right
	if (*cur->data > target) retrieveHelper(cur->left, target, holder); // if data is greater than target, go left
	return false;
}

//-------------------------------- getHeight --------------------------------
// Returns height of a given node in BST
// If node is leaf, height = 1
// Uses helper function getHeightHelper
// Preconditions: NONE
// Postconditions: BST remains unchanged
// --------------------------------------------------------------------------
int BinTree::getHeight(const NodeData& root) const {
	return getHeightHelper(root, this->root);
}

//---------------------------- getHeightHelper ------------------------------
// Helper function for getHeight
// Finds target node in tree if it exists
// Uses helper function getHeightOtherHelper
// Preconditions: NONE
// Postconditions: BST remains unchanged
int BinTree::getHeightHelper(const NodeData& target, Node* cur) const {
	if (!cur) return 0; // if cur is null return 0
	else if (*cur->data == target) return getHeightOtherHelper(cur); 
	else {
		int left = getHeightHelper(target, cur->left); // set left's value to left tree height 
		int right = getHeightHelper(target, cur->right); // set right's value to right tree height

		return max(left, right);  // return maximum value
	}
}

//---------------------------- getHeightOtherHelper -------------------------
// Helper function for getHeightHelper
// Returns height of root node
// --------------------------------------------------------------------------
int BinTree::getHeightOtherHelper(Node* cur) const { 
	if (!cur) return 0;
	else return 1 + max(getHeightOtherHelper(cur->left), getHeightOtherHelper(cur->right));
	// + 1 as one leaf node will count as 1 for height, and find max of left and right side
}

//------------------------------- bstreeToArray -----------------------------
// Builds a sorted array from a BST of NodeData
// BST is destructed after completion in the end
// Uses bstreeToArrayHelper function
// Preconditions: BST
// Postconditions: BST is deleted
// --------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arr[]) {
	bstreeToArrayHelper(this->root, arr);
	this->~BinTree();
}

//---------------------------- bstreeToArrayHelper --------------------------
// Helper function for bstreeToArray
// Sets bstree values to nullptr after completion
// --------------------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* cur, NodeData* arr[]) {
	if (!cur) return 0; // if cur is null then return 0
	int left = bstreeToArrayHelper(cur->left, arr); // set left to keep going to the left of array

	NodeData* temp = cur->data; // create temp node with cur's data which should be on the very left
	cur->data = nullptr; // set cur->data to nullptr, and then set array + left of temp's value
	*(arr + left) = temp;
	temp = nullptr; // set temp to nullptr

	int right = bstreeToArrayHelper(cur->right, 1 + arr + left); // now go right
	return left + right + 1; // return 1 + left + right
}

//------------------------------ arrayToBSTree ------------------------------
// Builds a balanced BST from an array of NodeData (assumes array is sorted)
// Array elements are set to nullptr in the end
// Uses arrayToBSTreeHelper function
// Preconditions: Sorted Array
// Postconditions: Array elements set to nullptr
// --------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[]) {
	this->~BinTree(); // call destructor to make tree empty
	int right = 0;
	for (int i = 0; i < 100; ++i) {
		if (arr[i] != nullptr) right++; // setting length of array
		else arr[i] = nullptr;
	}
	arrayToBSTreeHelper(this->root, arr, 0, right - 1); // call helper func
}

//---------------------------- arrayToBSTreeHelper --------------------------
// Helper function for arrayToBSTree
// Builds BST and sets array to nullptr after completion
// --------------------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node* cur, NodeData* arr[], int left, int right) {
	if (left > right) cur = nullptr; // if left is > right then cur will be set to nullptr
	else {
		int midpoint = left + (right - left) / 2; // set midpoint, doing it this way so it doesn't cause integer overflow
		NodeData* temp = arr[midpoint]; // temp nodedata set as root value through array's midpoint
		arr[midpoint] = nullptr;
		insert(temp); // insert that root
		arrayToBSTreeHelper(cur, arr, left, midpoint - 1); // recursively call to get first half of array from left side
		arrayToBSTreeHelper(cur, arr, midpoint + 1, right); // recursively call to get second half of array from right side
	}
	
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}