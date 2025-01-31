#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "List.h"
#include <limits>
using namespace std;

int userEntryFunction(void);
//Desc: Reads and returns user entries
//Pre: Needs to be called on
//Post: Returns user entry for what called it

int main()
{
	
	List linkedList;
	
	int choice;
	bool searchFound;

    while(true)
    {
        cout << "Please choose an option:" <<  endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Display List " << endl;
        cout << "5. Quit" << endl;


		cout << endl << "Your Choice:";
        cin >> choice;


        switch (choice)
        {
            case 1:
                cout << "You chose Insert. Please enter a value." << endl;
                linkedList.insert(userEntryFunction());
                break;
                
            case 2:
                cout << "You chose Search. Please enter which number you'd like to search for." << endl;
                searchFound = linkedList.search(userEntryFunction());
                if(searchFound == true)
                	cout << "Entry found in list.\n\n" << endl;
                else
                	cout << "Entry not found in list.\n\n" << endl;
                break;
                
            case 3:
                cout << "You chose Remove." << endl;
							
				// ok so idk why but if i put in something like this the code below then it breaks the remove function. 
				 
				//The only problem with not having something like this is that when the list is empty it prints "-1" but I think for now that's better than a broken remove 
				
				/*
					if (linkedList.remove() != -1)
				{		
					cout << linkedList.remove() << endl;
            	}
            	else
            	{
            		cout << "No Value to Remove!" << endl << "\n";
				}
				*/
						
				cout << linkedList.remove() << endl;
                break;
                
            case 4:
                cout << "Now displaying list..." << endl;
                cout << linkedList << endl;
                
               
                
                break;
                
            case 5:
                cout << "Exiting..." << endl;
                return false;
                
            default:
                cout << "Invalid option, try again." << endl;
                
                cin.clear();
                
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');		
				/*	^^^ found this code online to clear bad data from the input stream. Had issues with forever loop
				
					https://stackoverflow.com/questions/2256527/how-to-clear-the-unneccessary-input-stream-in-c 
					
					we probably have something like this in our notes from object oriented but i didn't wanna go digging and just looked the syntax up */
				break;
        }
    }	
}

int userEntryFunction(void)
{
	int userEntry;
	cin >> userEntry;
	return userEntry;
}
