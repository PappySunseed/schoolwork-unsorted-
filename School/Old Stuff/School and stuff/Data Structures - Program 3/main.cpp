
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstddef>
#include "db.h"

#define SIZE 5 // Size of array. No idea where array goes.

using namespace std;

int progChoices(void);
//Desc: Reads user entry for option
//Pre:  Needs to be called on
//Post: Returns respective user entry value for whatever called it

int valueEntry(int);
//Desc: Reads numeric values for user entry
//Pre:  Sends in a limit key for age or ID
//Post: Returns what user entered after data checks

string nameEntry(void);
//Desc: Sends string based on input
//Pre:  Needs to be called on at appropriate time
//Post: Returns what user typed after data validation

int main() {

	
	List linklist;
	dataBase d1;
	bool progRun = true;
	int opt;
	int IDtest;
	string nameTest;
	int Agetest;
	
	cout << "********** CHAIN HASHING DATABASE **********" << endl;
	
	while(progRun) {
		
		cout << "\nADD - Add a record to the database.\nDELETE - Remove a record from the database.\nSEARCH - Search database for a record.\nDISPLAY - Displays all data.\nQUIT - End program.\n" << endl;
		cout << ">> ";
		opt = progChoices();
		
		switch (opt) {
			
			case 1:
				cout << "ADD SELECTED." << endl;
				cout << "\nEnter an ID;\n>> ";
				IDtest = valueEntry(1);	// Calls for ID entry based on value passed in.
				cout << "Enter a Name;\n>> ";
				nameTest = nameEntry();
				cout << "Enter an Age;\n>> ";
				Agetest = valueEntry(2);	// Calls for Age entry based on value passed in.
				
				d1.hash(IDtest, nameTest, Agetest);
				
				//d1.insert(IDtest, nameTest, Agetest);
				
				break;
				
			case 2:
				// Will eventually prompt for user entry to see what ID # they're deleting
				cout << "DELETE SELECTED." << endl;
				cout << ">> ";
				cout << "TYPE IN ID TO DELETE. \n" << endl;
				IDtest = valueEntry(1);
				d1.remove(IDtest);
				break;
				
			case 3:
				// Will eventually prompt for user entry to see what ID # they're looking for.
				// Currently just prints the test data.
				cout << "SEARCH SELECTED.\n" << endl;
				cout << "TYPE IN ID TO SEARCH FOR. \n" << endl;
				IDtest = valueEntry(1);
				d1.search(IDtest);
				break;
			case 4:
				cout << "DISPLAY SELECTED." << endl;
				cout << d1;
				
				break;
			case 5:
				progRun = false;
				exit(0);
				
			default:
				cout << "Not an Option; Try again." << endl;
			
		}	// Closes "progOptions" switch
		
	}	// Closes "progRun" while loop

	return 0;
	
}

int progChoices(void) {	

	string userEntry;
	int userEntryInt;
	getline(cin, userEntry);
	
	// Found similar code within book.
	for(int i = 0; i < userEntry.size(); i++) {
    	userEntry.at(i) = toupper(userEntry.at(i));
	}

	// Translates String Selection to Integer for SwitchCase
	if(userEntry == "ADD")
		userEntryInt = 1;
	else if(userEntry == "DELETE")
		userEntryInt = 2;
	else if(userEntry == "SEARCH")
		userEntryInt = 3;
	else if(userEntry == "DISPLAY")
		userEntryInt = 4;
	else if(userEntry == "QUIT")
		userEntryInt = 5;
	else
		userEntryInt = 6;	
	
	return userEntryInt;
}

int valueEntry(int entryKey) {

	string userInput;
	int returnVal;
	bool badVal = true;
	
	getline(cin, userInput);
	
	while (badVal) {
	// Handles initial check for characters in entry.
	
		size_t found = userInput.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		if (found != std::string::npos) {
			cout << "Only use numbers; Try again." << endl;
			cout << ">> ";
			getline(cin, userInput);
		}
		else {
			badVal = false;
		}
	}
	if(entryKey == 1) {	
	// entryKey 1 handles ID Error Check.
	
		returnVal = stoi(userInput);
		
		while (returnVal > 9999 || returnVal < 0) {
			badVal = true;
			cout << "Bad ID; Enter ID value 0 - 9999." << endl;
			cout << ">> ";
			getline(cin, userInput);
			while (badVal) {
				size_t found = userInput.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != std::string::npos) {
					cout << "Only use numbers; Try again." << endl;
					cout << ">> ";
					getline(cin, userInput);
					badVal = true;
				}
				else {
					badVal = false;
					returnVal = stoi(userInput);
				}
			}	// Close character while loop
		}	// Close number while loop
		
		return returnVal;
	}
	else if(entryKey == 2) {
	// entryKey 2 handles Age Error Check
	
		returnVal = stoi(userInput);
		
		while (returnVal > 125 || returnVal < 0) {
			badVal = true;
			cout << "Bad Age; Enter Ige value 0 - 125." << endl;
			cout << ">> ";
			getline(cin, userInput);
			while (badVal) {
				size_t found = userInput.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != std::string::npos) {
					cout << "Only use numbers; Try again." << endl;
					cout << ">> ";
					getline(cin, userInput);
					badVal = true;
				}
				else {
					badVal = false;
					returnVal = stoi(userInput);
				}
			}	// Close character while loop
		}	// Close number while loop
		
		return returnVal;
	}
	else {
		// Should be impossible. Should still include.
		cout << "FATAL ERROR;" << endl;
		exit(-1);
	}

	return returnVal;
	
}	// Closes Function

string nameEntry(void) {
	
	string name;
	string returnName;
	bool badName = true;
	
	getline(cin, name);
	
	while (badName == true) {
	// Handles initial check for characters in entry.
	
		size_t found = name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ");
		if (found != std::string::npos) {
			name.clear();
			cout << "Only use letters; Try again." << endl;
			cout << ">> ";
			getline(cin, name);
		}
		else if (name.length() > 30) {
			name.clear();
			cout << "Name entered must be less than 30 characters; Try again." << endl;
			cout << ">> ";
			getline(cin, name);
		}
		else
			badName = false;
			returnName = name;
			name.clear();
	}
	return returnName;
}