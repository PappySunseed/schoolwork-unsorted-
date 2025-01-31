#include "graph.h"

using namespace std;

Graph::Graph(int numVertices) : numVertices(numVertices) 
{
    adjMatrix.resize(numVertices, std::vector<bool>(numVertices, false));
    currentTop[numVertices];
}

void Graph::addEdge(int i, int j) {
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
}

void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = false;
    adjMatrix[j][i] = false;
}

void Graph::printGraph() 
{
    for (int i = 0; i < numVertices; i++) {
        cout << i+1 << ": ";
        for (bool j : adjMatrix[i]) {
            if(j == true) {
            	cout << 1 << " ";
			}
			else if(j == false) {
				cout << 0 << " ";
			}
        }
        cout << "\n";
    }
}

bool Graph::isEdge(int i, int j)
{
	if(adjMatrix[i][j] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Graph::IsnewDomSet(int set[])
{
	int minNodes = 0;
	int challengerNodes = 0;
	
	for(int i = 0; i < SIZE; i++)
	{
		if(set[i] == 2)
		{
			challengerNodes++;
		}
		if(currentTop[i] == 2)
		{
			minNodes++;
		}
	}
	
	if(minNodes == 0 || challengerNodes < minNodes)
	{
		for(int i = 0; i < SIZE; i++)
		{
			currentTop[i] = set[i];
		}
		
		cout << "\nNew min_dominating set found: n = ";
		for (int i = 0; i < SIZE; i++) {
			cout << currentTop[i];
		}
		cout << "\n\n" << endl;
		return challengerNodes;
	}
	else
	{
		cout << "\nPrevious set still minimum. n = ";
		for (int i = 0; i < SIZE; i++) {
			cout << currentTop[i];
		}
		cout << "\n\n" << endl;
		return minNodes;
	}
}
	