#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "db.h"
#include <string>

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
	//Current is set to head; temp is set to current
	//Current moves forward once in the list; temp is deleted.
	//Continues until current == nullptr at end of list
    current = head;
    do{
        temp = current;
        current = current -> next;
        delete temp;
    }while(current != nullptr);
    delete head;

    current = nullptr;
    head = nullptr;
    temp = nullptr;
}

//OVERLOADED << OPERATOR
ostream& operator<<(ostream& outp, const List& L)
{	
	Node *tempCur;
	tempCur = L.head;
	
	while(tempCur != nullptr)
	{
		outp << "ID Number: "<< tempCur -> IDdata << setw(5);
		outp << "Name: "<< tempCur -> nameData << setw(5);
		outp << "Age: "<< tempCur -> ageData << setw(5);
		
		outp << "\n";
		
		tempCur = tempCur -> next;
	}
	
	tempCur = nullptr;
	delete tempCur;
	
	//Occurs when list is empty.
	if (L.head == nullptr)
	{
		cout << "This Slot is Empty!" << endl;
	}	
	
	return outp;
}

// MODIFICATION MEMBER FUNCTIONS
//List Modification Members
void List::insert(const int userID, const string userName, const int userAge)
{

	//If list does not exist, creates head node. Occurs ONCE.
	if(head == nullptr)
	{
		head = new Node;
		head -> IDdata = userID;
		head -> nameData = userName;
		head -> ageData = userAge;

		head -> next = nullptr;
		current = head;
		
		//Included to keep track of what occurs when.
		cout << "Head Created\n\n" << endl;
	}
	else if(current -> next == nullptr)
	{
		temp = new Node;
		
		temp -> IDdata = userID;
		temp -> nameData = userName;
		temp -> ageData = userAge;
		
		current -> next = temp;
		temp -> next = nullptr;
		current = temp;
		temp = nullptr;
		
		//Included to keep track of what occurs when.
		cout << "Current -> Next == nullPtr; Adding to end of list.\n\n" << endl;
	}
	//This portion of the if/elseIf can only be accessed when users search for an entry before calling insert.
	else if(current -> next != nullptr)
	{
		temp = new Node;
		
		temp -> IDdata = userID;
		temp -> nameData = userName;
		temp -> ageData = userAge;	
			
		temp -> next = current -> next;
		current -> next = temp;
		current = temp;
		temp = nullptr;
		
		//Included to keep track of what occurs when.
		cout << "Current -> Next != nullPtr; Adding node between nodes.\n\n" << endl;
	}

	
}








//	vvv	DATABASE FUNCTIONS	vvv    ----------------------------

//database constructor 
dataBase::dataBase()
{
	List L[5];
}

//database destructor 
dataBase::~dataBase()
{
}


//MODIFICATION MEMBERS 
	
	//overloaded output 
ostream& operator<<(ostream& outp, List L[])
{
	for(int i=0; i<5; i++)
	{
		outp << "Slot "<< i << ":\n" <<L[i] << "\n\n";
	}
}

	//search function
bool dataBase::search(const int userID)
{

	int entry;
	
	current = head;
	
	bool found = false;
	
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

	//remove function
int dataBase::remove(const int userID)
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


