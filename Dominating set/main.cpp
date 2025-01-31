/*

	Analysis of Algorithms
	Graph Assignment
	Caleb Massey, Caleb Rachocki, Caleb Ruby, Adir Turgeman
	Due November 8th, 5:50pm

*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "graph.h"

using namespace std;

///not needed, keot for reference 
/*void pickNode(Graph g, int node, int dominated[])    
{
    for(int i; i++; i < SIZE)
    {    	
        if (g.isEdge(node,i))
            dominated[i] = 1;
    }
    
    dominated[node] = 2;
    
    return;
}*/

bool IS_dominating(Graph g, int set[]);
// DESC: Tests to see what current combination is dominating
// PRE: Requires adj. matrix + binary combination
// POST: 

bool simulateEvent(int);
// DESC: Simulates a percentage chance
// PRE: Requires PROBABILITY constant
// POST: Outputs our "percentage"

int main() {
    
	// Initialize graph with SIZE # of nodes
	Graph g(SIZE);
	
	// Seed the random number generator
   	srand((unsigned) time(0));
	
	// Temporarily holds our binary number. Copies into exiting array.
	int binaryCounter[SIZE] = {0};
	int binaryCopy[SIZE] = {0};

    bool allOnes = false;              // Tracks all binary digits up to current
    bool allZeros = true;              // Needed to initialize counter
    bool notFirstIteration = false;
    bool isBestSet = false;

   	// Determines number of possible binary combos
   	long long runningLimit = 0;
   	runningLimit = pow(2, SIZE);

    int priorDigitsAmt = 0;            // Number of previous digits before current
    int printLoop = 0;                 // printLoop. Delete later.
    int steppingUnit = 0;              // Used to step through the binaryCounter array
    int saveSlot = 0;                  // Saves current slot when we do not have all 1s prior
    int zeroLoop, oneLoop, mainLoop;
    int i, b, k, w, a;
    int zeroOut = 0;

	// Form the adjacency matrix
	for(int i = 0; i < SIZE; i++) {
	    for(int b = i; b < SIZE; b++) {

			// Simulate the event with the given probability
	    	bool result = simulateEvent(PROBABILITY);
	    	
			if(result == true && i != b) { 
				g.addEdge(i, b);
			}
		
		}
	}
////////////////////////////////////////////////////////////////////
	// BRUTE-FORCE METHOD
	
    // While we still have possible combos...
    while (runningLimit > 0) {
        runningLimit--;

		// Clear copy array for every iteration
		for(a = 0; a < SIZE; a++) {
			binaryCopy[a] = 0;
		}

		// Copy array
		for (w = 0; w < SIZE; w++) {
			binaryCopy[w] = binaryCounter[w];
		}
		
		// Pass current Brute-Force combo to determine if best set
		isBestSet = IS_dominating(g, binaryCopy);
		
		// If set is dominating, send it to challenge current best set
		if(isBestSet == true) {
			g.IsnewDomSet(binaryCopy);
		}

        if (notFirstIteration) {

            // Check every digit up to current
            for (mainLoop = 0; mainLoop < priorDigitsAmt; mainLoop++) {

                // If current binary digit is 0...
                if (binaryCounter[mainLoop] == 0) {

                    // Check all digits up to current
                    for (zeroLoop = 0; zeroLoop < priorDigitsAmt; zeroLoop++) {
                        switch (binaryCounter[zeroLoop]) {
                            case 0:
                                allOnes = false;
                                saveSlot = zeroLoop;
                                zeroLoop = SIZE + 1;
                                break;

                            case 1:
                                allOnes = true;
                                break;

                            default:
                                break;
                            }
                        }

                        // If not all ones, current digit is now a 1
                        if (!allOnes) {
                            binaryCounter[saveSlot] = 1;
                            for (k = 0; k < saveSlot; k++) {
                                binaryCounter[k] = 0;
                            }
                            mainLoop = SIZE + 1;
                        }
                        else if (allOnes) {
                            mainLoop = SIZE + 1;
                        }
                    }

                    // If current binary digit is 1...
                    if (binaryCounter[mainLoop] == 1) {

                        // Check all digits up to current
                        for (oneLoop = 0; oneLoop < priorDigitsAmt; oneLoop++) {
                            
							switch (binaryCounter[oneLoop]) {
                            	case 0:
                                	allOnes = false;
                                    saveSlot = oneLoop;
                                    oneLoop = SIZE + 1;
                                    break;
								
                            	case 1:
                                	allOnes = true;
                                	break;
								
                            	default:
                                	break;
                            }
                        }

                        // If all ones, escape the loop
                        if (allOnes) {
                            mainLoop = SIZE + 1;
                        }
                        else if (!allOnes) {
                            binaryCounter[saveSlot] = 1;
                            for (k = 0; k < saveSlot; k++) {
                                binaryCounter[k] = 0;
                            }
                            mainLoop = SIZE + 1;
                        }
					}
            }

            // Setup for next iteration of 'runningLimit' while loop
            mainLoop = 0;

        }

          // Occurs when all previous digits are a 1.
        if (allOnes && priorDigitsAmt != SIZE) {
            for (i = 0; i < priorDigitsAmt; i++) {
                binaryCounter[i] = 0;
            }
            binaryCounter[i] = 1;
            allOnes = false;
            priorDigitsAmt++;
        }

        // Initialize after testing w/ nothing.
        if (allZeros) {
               binaryCounter[0] = 1;
               priorDigitsAmt++;
               allZeros = false;
               notFirstIteration = true;
        }

    } // End of Brute Force	

////////////////////////////////////////////////////////////////////
// APPROXIMATION METHOD



// End of Approximation

////////////////////////////////////////////////////////////////////

	// Print our adjacency matrix
    g.printGraph();

    return 0;
    
}

bool IS_dominating(Graph g, int set[SIZE])
{
	
	bool isAnEdge = false;
	
	// Convert all 1's to 2's
    for(int i = 0; i < SIZE; i++)
    {
        if (set[i] == 1)
        {
            set[i] = 2;
        }
        
    }

	//
    for(int i = 0; i < SIZE; i++)
    {
        if(set[i] == 2)
        {
            for(int b = 0; b < SIZE; b++)
            {
            	
                if (g.isEdge(i, b) == true && set[b] != 2)
                {    
                    set[b] = 1;
                }           
            }
		}
    }    

/*
	// Feel free to uncomment. Just prints the current binary combo.
	for(int i = 0; i < SIZE; i++) {
		cout << set[i];
	}
	cout << endl;
*/

    // If we have an uncovered neighbor, return FALSE; Not a dominating set
    for(int i = 0; i < SIZE; i++)
    {
        if(set[i] == 0)
            {
                return false;
            }
    }
    
    // Otherwise, return TRUE
    return true;     
}

bool simulateEvent(int probability) 
{
	int random = (rand() % 100) + 1;
    return random < probability;
}
