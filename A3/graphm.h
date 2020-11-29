#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

int const MAXNODES_M = 101;							// Max size for T and C arrays
													// 101 because we start at 1
class GraphM {
public:
	GraphM();										// Default constructor
	void buildGraph(ifstream&);						// buildGraph function to create graph info read from file
	bool insertEdge(int from, int to, int dist);	// inserts edge
	bool removeEdge(int from, int to);				// removes edge
	void findShortestPath();						// Uses Djikstra's algorithm to find shortest path
	void display(int from, int to);					// displays node info from one node to another
	void displayAll();								// displays all info in graph
	void findAPath(int from, int to);				// helper function for display() and displayAll()
	void findData(int from, int to);				// helper function for display()
private:
	struct TableType {
		bool visited;								// if a node has been visited or not
		int dist;									// shortest distance from source
		int path;									// previous node of min distance
	};

	NodeData data[MAXNODES_M];						// data for graph nodes 
	int C[MAXNODES_M][MAXNODES_M];				    // Cost array, the adjacency matrix
	int size;										// number of nodes in the graph
	TableType T[MAXNODES_M][MAXNODES_M];			// stores visited, distance, path

};
#endif