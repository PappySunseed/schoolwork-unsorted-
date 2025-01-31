#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "List.h"
#include<limits>
using namespace std;

int main(){

	List list1;
	sortList sort1;

	int  userOption;
	int  userOptionTwo;
	int  userEntry;
	
	cout << "Please select 1 for standard list, 2 for sorted list, or 3 to quit." << endl;
	cin >> userOption;

	//Switch case is for the userOption to decide what the program does... Code in case 1 and 2 will be similar. Default kills the program.
	//STANDARD LIST OPTION:
	if(userOption == 1)
	{
		cout << "Standard List Selected:\nPress 1 to Insert, 2 to Print, or 3 to Quit: ";
		cin >> userOptionTwo;
		while(userOptionTwo == 1 || userOptionTwo == 2)
		{
			switch(userOptionTwo)
			{	
				case 1:
					cout << "\nEnter Number: ";
					cin >> userEntry;
					list1.insert(userEntry);
					
					
					cout << "Press 1 to Continue, 2 to Print, or 3 to Quit: ";
					cin >> userOptionTwo;
					break;               
					
			    case 2:
					cout << "Printing List...\n";
					list1.display();
					userOptionTwo = 3;	//Allows the program to exit the while loop.
					break;

				default:
					cout << "Quitting...";
					break;
			}
		}		
	}
		
	//SORTED LIST OPTION:
	if(userOption == 2)
	{
		cout << "Sorted List Selected:\nPress 1 to Insert, 2 to Print, or 3 to Quit: ";
		cin >> userOptionTwo;
		while(userOptionTwo == 1 || userOptionTwo == 2)
		{
			switch(userOptionTwo)
			{	
				case 1:
					cout << "\nEnter Number: ";
					cin >> userEntry;
				
				
					sort1.insert(userEntry);
					
					
					cout << "Press 1 to Continue, 2 to Print, or 3 to Quit: ";
					cin >> userOptionTwo;
					break;               
					
			    case 2:
					cout << "Printing List...\n";
					sort1.display();
					userOptionTwo = 3;	//Allows the program to exit the while loop.
					break;

				default:
					cout << "Quitting...";
					break;
			}
		}		
	}
	
	//QUIT PROGRAM OPTION:
	else
	{
		cout << "Quitting..." << endl;
	}
}	