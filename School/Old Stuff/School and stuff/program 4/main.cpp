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
	
	List list1;
	List list2;
	
	int continueRun = 1;
	int userOption;
	int rem;								//value to be subtracted. changes in each case
	
	while(continueRun == 1)
	{
		cout << "Please select what to do;\n1 for inserting to list1\n2 for inserting to list2"
		"\n3 for adding lists into list1\n4 for adding lists into list2\n5 to remove a value from list1"
		"\n6 to remove a value from list2\n7 to display list1\n8 to display list2\n9 to quit.\n" << endl;
		cin >> userOption;
		
		switch(userOption)
		{
			//LIST1 INSERT OPTION
			case 1: 
				cout << "Enter numeric value: ";
				list1.insert(userEntryFunction());
				cout << endl;
				break;

			//LIST2 INSERT OPTION
			case 2:
				cout << "Enter numeric value: ";
				list2.insert(userEntryFunction());
				break;

			//ADD LISTS W/ OUTPUT TO LIST1
			case 3:
				list1 = list1+list2;
				break;

			//ADD LISTS W/ OUTPUT TO LIST2
			case 4:
				list2 = list1+list2;
				break;

			//REMOVE VALUE FROM LIST1
			case 5:
				cout << "Enter value to be removed.\n";
				
				cin >> rem;			
				
				list1 = list1 - rem;
				
				break;

			//REMOVE VALUE FROM LIST2
			case 6:
				cout << "Enter value to be removed.\n";

				cin >> rem;			
				
				list2 = list2 - rem;
		
				break;

			//DISPLAY LIST1
			case 7:
				cout << "List 1:\n" << list1;
				break;

			//DISPLAY LIST2
			case 8:
				cout << "List 2:\n" << list2;
				break;

			//QUIT
			case 9:
				continueRun = 0;	//breaks while loop, kills program.
				cout << "Quitting program...";
				break;
		}
	}
}

//I added this for the sake of easier to read and write code. We don't need to write these 3 lines 4 times...
//Should be able to use this for "subtracting" values too, since it just reads user input.
int userEntryFunction(void)
{
	int userEntry;
	cin >> userEntry;
	return userEntry;
}