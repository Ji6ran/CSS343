#include "graphm.h"
#include <algorithm>
#include <climits>
#include <iomanip>


// --------------------------- Default Constructor -------------------------
// Constructs empty table and initializes value inside table
// -------------------------------------------------------------------------
GraphM::GraphM() {
	size = 0;
	for (int i = 1; i < MAXNODES_M; ++i) {
		for (int j = 1; j < MAXNODES_M; ++j) {
			C[i][j] = INT_MAX; // fill each slot with infinity
			T[i][j].visited = false; // set visited to false
			T[i][j].dist = INT_MAX; // set the distance to infinity
			T[i][j].path = 0; // set path to 0
		}
	}
}
// ------------------------ buildGraph(ifstream&) --------------------------
// Builds graph node info and matrix of adjacent edges between each node
// read from file
// -------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile) {
	infile >> size; // sets size
	string name = ""; // name for each node
	getline(infile, name); // read line from file

	for (int i = 1; i <= size; ++i) 
		data[i].setData(infile); // set all node names
	int to, from, dist; 
	while (infile >> from >> to >> dist) {
		if (from == 0) break; // read file until from is 0
		C[from][to] = dist; // sets cost array table
	}
}
// -------------------- findShortestPath() ---------------------------------
// Finds shortest path from one node to every other node using Djikstra's 
// algorithm
// -------------------------------------------------------------------------
void GraphM::findShortestPath() {
	for (int source = 1; source <= size; ++source) {
		T[source][source].dist = 0; // set initial dist to 0 and visited to true (visiting itself)
		T[source][source].visited = true;
		for (int i = 1; i <= size; ++i) { 
			if (C[source][i] != INT_MAX) { // copy distances from cost array into table's distance
										// and set path = to the source if distances are not infinity
				T[source][i].dist = C[source][i];
				T[source][i].path = source;
			}
		}
		int v = -1; // smallest vertex
		while (v != 0) { // while vertex isn't 0
			v = 0; // set it to 0 so that if distances in cost array are less than min distance
					// it will skip that and break out of the loop once v becomes 0.
			int min = INT_MAX;
			for (int i = 1; i <= size; ++i) {
				if (C[source][i] < min && !(T[source][i].visited)) {
					v = i; // smallest vertex set to current index
					min = C[source][i]; // min set to distances in cost array
				}
			}
			if (v == 0) break;
			T[source][v].visited = true; // set visited to true
			for (int w = 1; w <= size; ++w) {
				if (T[source][w].visited) continue; // checks for if something is already visited, continue to next iteration
				if (C[v][w] == INT_MAX) continue; // if w adjacent to v is infinity, continue
				if (T[source][w].dist > T[source][v].dist + C[v][w]) {
					// if adjacent w is > smallest vertex's distance + w adjacent to v, set it = to that
					T[source][w].dist = T[source][v].dist + C[v][w];
					T[source][w].path = v; // set path = to vertex
				}
			}
		}
	}
}
// -------------------------- insertEdge(int, int) -------------------------
// Inserts an edge in graph between 2 nodes (ints)
// -------------------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int dist) {
	if (from > size || from < 1) return false; // if from is greater than size or less than 1, return false
	if (to > size || to < 1) return false; // if to is greater than size or less than 1, return false
	if (dist != 0 && from == to) return false; // if dist isn't 0 and from is same as to, return false
	if (dist < 0) return false; // if dist is negative, return false

	C[from][to] = dist; // insert edge
	findShortestPath();
	return true;
}
// --------------------------- removeEdge(int, int) ------------------------
// Removes an edge in graph between 2 nodes (ints)
// -------------------------------------------------------------------------
bool GraphM::removeEdge(int from, int to) {
	if (from > size || from < 1) return false; // if from is greater than size or less than 1, return false
	if (to > size || to < 1) return false; // if to is greater than size or less than 1, return false
	C[from][to] = INT_MAX; // remove edge
	findShortestPath();
	return true;
}
// ----------------------------- findAPath(int, int) -----------------------
// Finds a path for an edge using recursion
// Helper function for displayAll() and display()
// -------------------------------------------------------------------------
void GraphM::findAPath(int from, int to) {
	if (from == to) { // if they're the same, print out to and return
		cout << to << " ";
		return;
	}
	int pathInfo = to; // assign "to" to pathInfo
	findAPath(from, to = T[from][to].path); // recursive call where to is assigned the next path
	cout << pathInfo << " "; 
}
// ------------------------------ findData(int, int) -----------------------
// Finds data for edge distance using recursion
// Helper function for display()
// -------------------------------------------------------------------------
void GraphM::findData(int from, int to) {
	if (from == to) { // if from and to are the same, print data at index to and return
		cout << data[to] << " ";
		return;
	}

	int nodeInfo = to; // assign "to" to nodeInfo
	findData(from, to = T[from][to].path);  // recursive call where to is assigned next path
	cout << data[nodeInfo] << endl << endl;
}

// --------------------------- display(int,int) ----------------------------
// Displays the shortest distance with path info between from and to nodes
// Uses helper functions findAPath() and findData()
// -------------------------------------------------------------------------
void GraphM::display(int from, int to) {
	if ((from > size || from < 0) || (to > size || to < 0)) { //if edge exists
		cout << setw(7) << from << setw(7) << to; 
		cout << setw(14) << "---" << endl; 
		return;
	}
	cout << setw(7) << from << setw(7) << to;   // print node from and to data
	if (T[from][to].dist != INT_MAX) {   // check if adj node is not infinity
		cout << setw(12) << T[from][to].dist << setw(12);
		findAPath(from, to); // call findAPath
		cout << endl;
		findData(from, to); // call findData
	}
	else cout << setw(12) << "---" << endl;
	cout << endl;
	
}
// ------------------------------- displayAll() ----------------------------
// Displays all info in graph to show Djikstra's algorithm
// Uses helper function findAPath()
// -------------------------------------------------------------------------
void GraphM::displayAll() {
	cout << "Description" << setw(20) << "From Node" << setw(10) <<
		"To Node" << setw(14) << "Djikstra's" << setw(8) << "Path" << endl;
	// table titles ^
	for (int from = 1; from <= size; ++from) {
		cout << data[from] << endl << endl; // node name
		for (int to = 1; to <= size; to++) {
			if (T[from][to].dist != 0) { // if adj node's distance is not 0
				cout << setw(27) << from << setw(10) << to; // print from and to node
				if (T[from][to].dist == INT_MAX) // if adj node distance is infinity
					cout << setw(11) << "---" << endl; // print --- as there are no nodes
				else {
					cout << setw(12) << T[from][to].dist; // print dist
					cout << setw(10);

					findAPath(from, to);
					cout << endl;
				}
			}
		}
	}
}

