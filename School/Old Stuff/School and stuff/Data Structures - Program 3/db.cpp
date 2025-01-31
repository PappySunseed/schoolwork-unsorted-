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
		outp << "ID Number: "<< tempCur -> IDdata << "   ";
		outp << "Name: "<< tempCur -> nameData << "   ";
		outp << "Age: "<< tempCur -> ageData << "   ";
		
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

	//search function
void List::search(const int userID)
{
	
	int entry = userID;
	current = head;
	bool found = false;
	
	//Asking if the list even exists.
	if(current != nullptr)
	{
		//Loop occurs until value is either found or determined to not exist
		if(found == false)
		{
			//Loop occurs until current hits end of list
			while(current != nullptr)
			{	
				if(current -> IDdata == entry)
				{
					cout << "ID: " << current -> IDdata << endl;
					cout << "NAME: " << current -> nameData << endl;
					cout << "AGE: " << current -> ageData << endl;
					found = true;
					break;
				}
				else if(current -> IDdata != entry || current -> next == nullptr)
				{
					cout << "NOT FOUND!" << endl;
					break;
				}
				else
				{
					current = current -> next;
					found = false;
				}
			}
		}
	}
	else
	{
		cout << "\n List not found. Please enter data first.\n";
		return;
	}
}

	//remove function
int List::remove(const int userID)
{	
	
	int entry = userID;
	current = head;
	bool found = false;
	
	//Asking if the list even exists.
	if(current != nullptr)
	{
		//Loop occurs until value is either found or determined to not exist
		if(found == false)
		{
			//Loop occurs until current hits end of list
			while(current != nullptr)
			{	
				if(current -> IDdata == entry && current == head)
				{
					temp = head;
					head = head -> next;
					delete temp;
					
					//cout << "\n Removed: ";
					return userID;
				}
				else if(current -> IDdata == entry) {
					delete current;
				
					//cout << "\n Removed: ";
					return userID;
				}
				else if(current -> IDdata != entry || current -> next == nullptr)
				{
					cout << "Could not find: " << endl;
					return userID;
				}
				else
				{
					current = current -> next;
					found = false;
				}
			}
		}
	}
	else
	{
		cout << "List is empty, add data first.";
		return -1;
	}
	
}

//	vvv	DATABASE FUNCTIONS	vvv    ----------------------------

//database constructor 
dataBase::dataBase()
{
}

//database destructor 
dataBase::~dataBase()
{
	
}


//MODIFICATION MEMBERS 
	//insert/hashing function
void dataBase::hash(const int userID, const string userName, const int userAge)
{
	int key = userID % 5;
	
	arr[key].insert(userID, userName, userAge);
	return;
}

	//remove function
int dataBase::remove(const int userID)
{
	int key = userID % 5;
	
	arr[key].remove(userID);
	
	cout << "\nremoved: " << userID;
	return userID; 
}
	
	//search function
void dataBase::search(const int userID)
{
	int key = userID % 5;
	
	arr[key].search(userID);
	
	return;
}

	//overloaded output 
ostream& operator<<(ostream& outp, const dataBase& d1)
{
	for(int i=0; i<5; i++)
	{
		outp << "Slot "<< i << ":\n" <<d1.arr[i] << "\n\n";
	}
	return outp;
}




