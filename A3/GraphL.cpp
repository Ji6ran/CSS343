#include "graphl.h"
#include <iomanip>

// -------------------------- Default Constructor --------------------------
// Default constructor initializes size to 0 and sets visited to false 
// and data and edgeHead to nullptr at each index
// -------------------------------------------------------------------------
GraphL::GraphL() {
	size = 0;
	for (int i = 0; i < MAXNODES_L; ++i) {
		nodeArray[i].visited = false;
		nodeArray[i].edgeHead = nullptr;
		nodeArray[i].data = nullptr;
	}
}

// ------------------------------- Destructor ------------------------------
// Destructs object
// Uses helper function makeEmpty()
// -------------------------------------------------------------------------
GraphL::~GraphL() {
	makeEmpty();
}

// -------------------------------makeEmpty()-------------------------------
// Deletes graph object
// Helper function for destructor
// -------------------------------------------------------------------------
void GraphL::makeEmpty() {
	for (int i = 1; i <= size; ++i) {
		nodeArray[i].visited = false; // set all visited to false
		delete nodeArray[i].data; // delete the data inside then set data to null
		nodeArray[i].data = nullptr;

		if (nodeArray[i].edgeHead != nullptr) { // if edgeHead is not null
			EdgeNode* cur = nodeArray[i].edgeHead; // create temp variable to store
												// edgehead
			while (cur != nullptr) { // while it's not null
				// set each edgeHead to its next node, delete, and set it to null
				// after that set del to the current edgeHead
				nodeArray[i].edgeHead = nodeArray[i].edgeHead->nextEdge;
				delete cur;
				cur = nullptr;
				cur = nodeArray[i].edgeHead;
			}
		}
	}
}
// ------------------------ buildGraph(ifstream&) --------------------------
// Builds graph node info and adjacent edges between each node 
// read from file
// -------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile) {
	infile >> size;
	string name = "";
	getline(infile, name); // reads from file and sets in name string
	for (int i = 1; i <= size; ++i) {
		getline(infile, name);
		NodeData* temp = new NodeData(name); // temp nodedata contains data info
									// read from file which is stored in "name"
		nodeArray[i].data = temp; // sets each data from that temp nodeData
	}
	int to, from; // create to and from, same concept used in GraphM.cpp
	while (infile >> from >> to) {
		if (from == 0) break; // if from is 0, break out of loop
		if (nodeArray[from].edgeHead == nullptr) { // if nodeArray at from index's
												// edgeHead is null
			EdgeNode* node = new EdgeNode(); // create new edgenode
			node->adjGraphNode = to; // set adjacent node to "to" 
			nodeArray[from].edgeHead = node; // set the edgeHead to new node
			nodeArray[from].edgeHead->nextEdge = nullptr; // set next to null
		}
		else {
			EdgeNode* node = new EdgeNode(); // if nodeArray at from index's edgehead
												// is not null, create new node
			node->adjGraphNode = to; // set adjacent node to "to"
			node->nextEdge = nodeArray[from].edgeHead; // set nextEdge to edgeHead at
													// from index
			nodeArray[from].edgeHead = node; // then set edgeHead at from index to node
		}
	}
}

// -----------------------------displayGraph() -----------------------------
// Displays the entire graph's info with nodes and edges
// -------------------------------------------------------------------------
void GraphL::displayGraph() {
	EdgeNode* cur;
	cout << "Graph: \n"; 
	for (int i = 1; i <= size; ++i) {
		if (nodeArray[i].edgeHead != nullptr) { // if edgeHead is not null at cur index
			cout << "Node" << i << endl; 
			cout << setw(8) << *nodeArray[i].data << endl; // print out the data
			cur = nodeArray[i].edgeHead; // set cur to edgeHead at current index
			while (cur != nullptr) { // while cur is not null
				cout << setw(7) << "edge " << i << " "; // format
				cout << cur->adjGraphNode << endl; // getting adjacent node
				cur = cur->nextEdge; // setting cur to next node(edge)
			}
		}
	}
	cout << endl;
}

// -------------------------depthFirstSearch() -----------------------------
// Uses depth first search and displays each node
// -------------------------------------------------------------------------
void GraphL::depthFirstSearch() {
	cout << "Depth-first ordering: "; // 
	for (int i = 1; i <= size; ++i)
		if (nodeArray[i].edgeHead != nullptr && !(nodeArray[i].visited)) DFSHelper(i);
	cout << "\n" << endl;
}

// ---------------------------- DFSHelper(int) -----------------------------
// Helper function for depthFirstSearch()
// -------------------------------------------------------------------------
void GraphL::DFSHelper(int v) { 
	EdgeNode* cur = nullptr; 
	nodeArray[v].visited = true; // set visited to true
	cout << v << " "; // print out data passed in
	cur = nodeArray[v].edgeHead; // set cur to edgeHead at v index
	while (cur != nullptr) { // while cur is not null
		if (!nodeArray[cur->adjGraphNode].visited) DFSHelper(cur->adjGraphNode);
		// if adjacent node at cur is not visited, recursive call with new int being
			// cur's adjacent.
		else cur = cur->nextEdge;
	}
}