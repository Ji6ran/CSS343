#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
using namespace std;

int const MAXNODES_L = 101;

class GraphL {
public:
	GraphL();							// Default constructor							
	~GraphL();							// Destructor									
																						
	void buildGraph(ifstream&);			// builds graph reading from file				
	void displayGraph();				// displays full graph							
	void depthFirstSearch();			// Uses depth first search to find node in graph
	void DFSHelper(int v);				// Helper function for depthFirstSearch() function
																						
private:																				
	int size;							// # of nodes									
	struct EdgeNode;																	
	struct GraphNode {																	
		EdgeNode* edgeHead;				// head of list of edges						
		NodeData* data;					// data for each node							
		bool visited;					// whether node has been visited or not			
	};																					
	GraphNode nodeArray[MAXNODES_L];	// array with max size							
	struct EdgeNode {																	
		int adjGraphNode;				// adjacent graph node info						
		EdgeNode* nextEdge;				// next node									
	};																					
																						
	void makeEmpty();					// makeEmpty function for destructor			
	

};
#endif GRAPHL_H