#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "List.h"

using namespace std;

int main(){
	
	List list1;	
	sortedList sort1;
	
	int userOption;
	char userOptionTwo;
	int userEntry;
	
	
	
	cout << "Please select 1 for standard list, 2 for sorted list, or 3 to quit." << endl;
	cin >> userOption;

	//Switch case is for the userOption to decide what the program does... Code in case 1 and 2 will be similar. Default kills the program.
	switch(userOption)
	{
		case 1:
			cout << "Standard List Selected" << endl;
			cout << "Would you like to enter a number? (y/n) ";
			cin >> userOptionTwo;
			
			//Allows the user to decide when they're done entering values.
			if (userOptionTwo == 'y')
			{	//Allows the user to continue entering variables until finished.
				while (userOptionTwo == 'y')
				{
					cout << "Enter Number: ";
					cin >> userEntry;
					list1.insert(userEntry);		//This will eventually put user entries into the dynamic array
					cout << "Would you like to enter a number? (y/n) ";
					cin >> userOptionTwo;
				}
			}
			else
			{
				break;
			}
			
			
			list1.display();
			break;
			
		case 2:
			cout << "Sorted list selected" << endl;
			cout << "Would you like to enter a number? (y/n) ";
			cin >> userOptionTwo;
			
			//Allows the user to decide when they're done entering values.
			if (userOptionTwo == 'y')
			{	//Allows the user to continue entering variables until finished.
				while (userOptionTwo == 'y')
				{
					cout << "Enter Number: ";
					cin >> userEntry;
					sort1.inserts(userEntry);		//This will eventually put user entries into the dynamic array
					cout << "Would you like to enter a number? (y/n) ";
					cin >> userOptionTwo;
				}
			}
			else
			{
				break;
			}
			
			
			sort1.display();
			break;
		
		default:
			cout << "Quitting..." << endl;
			
			break;
	}

	
}