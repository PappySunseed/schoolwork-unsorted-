//	CLASS PROVIDED: Graph
//
// CONSTRUCTOR for the Graph Class
//	  Graph(int numVerticies)
//		Description: 		Safely and randomly generates our matrix
//		PreConditions: 		Requires total number of verticies
//		PostConditions: 	Randomized matrix is generated
//
// MODIFICATION MEMBER FUNCTIONS for the Graph Class
//		void addEdge(int i, int j);
//		  Description: 		Adds edges between nodes within adj. matrix
//		  PreConditions:  	Requires 'coordinates' i and j
//		  PostConditions:   Places edge based on coordinates
//
//		void removeEdge(int i, int j);
//		  Description: 		Removes an edge from adj. matrix
//		  PreConditions:  	Requires 'coordinates' i and j
//		  PostConditions: 	Removes edge based on coordinates
//    	
//		int IsnewDomSet(int set[]);
//		  Description: 		Determines if we keep current dom set, or replace with a better one
//		  PreConditions:  	Requires current and challenging dominating sets
//		  PostConditions: 	Replaces or keeps current based on comparison w/ challenger
//
// CONSTANT MEMBER FUNCTIONS for the List Class
//		void printGraph();
//		  Description: 		Prints the adjacency matrix
//		  PreConditions:  	Requires the adjacency matrix to be formed
//		  PostConditions: 	N/A
//
//		bool isEdge(int i, int j);
//		  Description: 		Determines if we have an edge between nodes
//		  PreConditions:  	Requires adjacency matrix 'location'
//		  PostConditions: 	Returns True/False based on data
//
// -----------------------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>

#define SIZE 14 				// Total number of nodes within graph
#define PROBABILITY 50		// Acts as percentage based number

using namespace std;

class Graph {

	private:
    	std::vector<std::vector<bool>> adjMatrix;		// Adjacency Matrix
    	int numVertices;								// Number of verticies
    	int currentTop[SIZE];							// Current best dominating set

	public:
		
		// CONSTRUCTOR
    	Graph(int numVertices);

		// MODIFICATION MEMBER FUNCTIONS
    	void addEdge(int i, int j);
    	void removeEdge(int i, int j);
    	int IsnewDomSet(int set[]);

		// CONSTANT MEMBER FUNCTIONS
    	void printGraph();
    	bool isEdge(int i, int j);

};

#endif
