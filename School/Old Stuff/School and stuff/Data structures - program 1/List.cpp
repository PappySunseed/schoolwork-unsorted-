#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "List.h"
#include <string>
#include <limits>
#include <cmath>
using namespace std;

//LIST CONSTRUCTOR
//Initializes head node to safe values; Can eventually be altered based on user entries.
List::List()
{
	count = 0;
	head = nullptr;
	temp = nullptr;
	current = nullptr;
}

//BASE CLASS DESTRUCTOR
List::~List()
{
	//Needs to delete the entire LL?
}

//OVERLOADED << OPERATOR
ostream& operator<<(ostream& outp, const List& L)
{	
	Node *tempCur;
	tempCur = L.head;
	int outputTracker = 0;

	while(tempCur != nullptr)
	{
		outp << tempCur -> storedNum << " ";
		tempCur = tempCur -> next;
		outputTracker++;
		
		if(outputTracker % 5 == 0)
		{
			outp << endl;
			outputTracker = 0;
		}
	}
	tempCur = nullptr;
	delete tempCur;
	
	if (L.head == nullptr)
	{
		cout << "List is Empty!" << endl;
	}	
	
	return outp;
}

bool checkIntInput(int &entry) 
{
    // Convert int to string
    string inputString = to_string(entry);
    // Find the first character that is not a digit
    size_t found = inputString.find_first_not_of("0123456789");
    // If a non-digit character is found, return false
    if (found != std::string::npos) 
	{
        return false;
    }
    return true;
}

// MODIFICATION MEMBER FUNCTIONS
//List Modification Members
void List::insert(const int entry)
{
	count++;
	
	int errCheck = entry;
	
	/*
	string tempString = to_string(entry);	
	bool bad;
	
	
	auto isFound = tempString.find_first_not_of("1234567890");
	
	if(isFound = std::string::npos)
	{
		bad = false;
	}

	if(bad=true)										
	{
		cout<< "bad data entered. please enter integer"<< endl;
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		
		return false;
	}*/
	
	
	if (!checkIntInput(errCheck)) 
	{
		cout << "Bad Data detected! Please try again, only including integers!";
		count --;
		Node* new_node = new Node;
        new_node->storedNum = 0;
        new_node->next = head;
        head = new_node;
        return;
    }
	

	//If list does not exist, creates head node. Occurs ONCE.
	if(head == nullptr)
	{
		head = new Node;
		head -> storedNum = entry;
		head -> next = nullptr;
		current = head;
		
		//DELETE WHEN PROGRAM IS COMPLETE; Here to help figure out what's happening.
		cout << "Head Created\n\n" << endl;
	}
	else if(current -> next == nullptr)
	{
		temp = new Node;
		temp -> storedNum = entry;
		current -> next = temp;
		temp -> next = nullptr;
		current = temp;
		temp = nullptr;
		
		//See line 74
		cout << "Current -> Next == nullPtr; Adding to end of list.\n\n" << endl;
	}
	//This portion of the if/elseIf can only be accessed when users search for an entry before calling insert.
	else if(current -> next != nullptr)
	{
		temp = new Node;
		temp -> storedNum = entry;
		temp -> next = current -> next;
		current -> next = temp;
		current = temp;
		temp = nullptr;
		
		//See line 74
		cout << "Current -> Next != nullPtr; Adding node between nodes.\n\n" << endl;
	}

	
}

bool List::search(const int entry)
{
	current = head;
	
	bool found = false;
	
	
	/*string tempString = to_string(entry);	
	bool bad;
	
	
	auto isFound = tempString.find_first_not_of("1234567890");
	
	if(isFound = std::string::npos)
	{
		bad = false;
	}

	if(bad=true)										
	{
		cout<< "bad data entered. please enter integer"<< endl;
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		
		return false;
	}*/
	
	//Asking if the list even exists.
	if(current != nullptr)
	{
		//Goes through the loop at least once to account for a possible "head -> storedNum == entry" scenario
		do
		{
			//If number exists, found = true.
			if(current -> storedNum == entry)
			{
				found = true;
				return found;
				break;
			}
			//If number is not found, and the current -> next is a nullptr, return false to exit loop
			else if(current -> storedNum != entry && current -> next == nullptr)
			{
				found = false;
				return found;
				break;
			}
			//If number is not found, step through list. Continues until either previous condition is met.
			else if(current -> storedNum != entry)
			{
				current = current -> next;
				found = false;
			}
		}while(found == false);
	}
	else
	{
		found = false;
	}
	return found;
}
	
int List::remove(void)
{	
	temp = head;
	
	if (!head)		//accounts for empty list
	{
		return -1;	
	}
	
	//Accounts for when only a head exists in the linked list. Shouldn't be an issue since deletion only occurs on demand.
	if(head -> next == nullptr)
	{
		int Num = head -> storedNum;
		delete head;
		head = nullptr;
		current = nullptr;
		return Num;
	}	
	
	//Moves temp through linked list until temp -> next == current
	while(temp -> next != current)
	{	
		temp = temp -> next;
	}

	if(temp -> next == current)
	{
		int Num = current -> storedNum;
		
		temp -> next = current -> next;
		delete current;
		current = temp;
		temp = nullptr;
		count --;
		return Num;
	}
	
	else 
	{
		return -1;
	}
}




