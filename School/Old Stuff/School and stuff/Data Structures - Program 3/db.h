
/*
-------------------------------------------------------------------------------------------------

	CLASS PROVIDED; LIST
	
	CONSTRUCTOR for List Class
	  List();
		Desc: Initializes safe values for count and node pointers
		Pre:  N/A
		Post: Count set to zero, head, temp, and current pointers set to nullptr
	
	DESTRUCTOR for the List Class
	  ~List();
	  	Desc: Deletes the linked list when program ends
	  	Pre:  Program must be told to end
	  	Post: Linked list is deleted, then the program ends.
	  	
	OVERLOADED OPERATORS;
	  friend ostream& operator<<(ostream&, const List&);
	  	Desc: Allows for printing of class List objects
	  	Pre:  Requires object of list to exist
	  	Post: Outputs any data values sotred within nodes of the List object
	  	
	MODIFICATION MEMEBERS;
	  void insert (const int entry);
	    Desc: Enters user entry into the LL based on current's location in said LL.
	    Pre:  Requires non-character userEntry from userEntryFunction() based in main.cpp
	    Post: Adds node with deired numeric value to the LL based on current's location in the LL

	  bool search (const int entry);
	    Desc: Steps through LL until desired data is found
		Pre:  Requires LL to exist and valid userEntry
		Post: Returns boolean value based on whether numeric value entered could be found in LL
		
	  int remove (void);
	    Desc: Removes a node from the LL
	    Pre:  Requires LL to exist
	    Post: Removes a node from the LL based on the current pointer's location in the LL;
	    
	CONSTANT MEMBERS;
		int count;
			desc: tracks number of iterations added to list 
			
		List pointers 
			Node* head;
			Node* current;
			Node* temp;
		
-------------------------------------------------------------------------------------------------
		
	STRUCT PROVIDED; NODE
	
	  int storedNum;
		Desc: Stores valid numeric entry
		Pre:  Requires userEntry
		Post: Value is stored within the node
		
	  Node* next;
	  	Desc: Pointer for movement through LL
	  	Pre:  Requires LL to exist
	  	Post: Moves through the LL to access values currently stored
		
-------------------------------------------------------------------------------------------------

	CLASS PROVIDED; DATABASE
	
	CONSTRUCTOR
		dataBase();
		Desc: initializes class
		Pre:  N/A
		Post: N/A
		
	DESTRUCTOR
		~dataBase();
		Desc: de-initializes class
		Pre:  N/A
		Post: N/A
	
	MODIFICATION MEMBERS 
		friend ostream& operator<<(ostream&, const dataBase&);
		Desc: Allows for printing of List array arr[5]
	  	Pre:  Requires class List and array of type List
	  	Post: Outputs all Lists held in the array. Calls overloaded List << operator for this purpose 
	  	
	  	void hash (const int userID, const string userName, const int userAge);
		Desc: inserts nodes into the correct linked list using a hashing algorith and key values
		Pre:  inputs of int UserID, string UserName, and int userAge as well as an insert function in class List
		Post: array of linked lists containing hashed data 
		
		int remove (const int userID);
		Desc: removes a node from a linked list in arr
		Pre:  input of int type userID, remove function in List class
		Post: hashes for the correct array slot, calls List remove function, outputs userID of removed node 
		
		void search(const int userID);
		Desc: searches for node based on userID and hash algorithm
		Pre:  int type userID, List search function
		Post: hashes for correct array slot, calls list search for correct node, outputs data found in that node 
	 

	
	CONSTANT MEMBERS
		List arr[5];
		Desc: array of type List objects
		Pre: Requires applicable class to be available 
		Post: Fills array with empty linked list objects


*/


#ifndef DB_H
#define DB_H
#include <cstdlib>

using namespace std;

struct Node
{
	int IDdata;
	string nameData;
	int ageData;
	
	Node* next;
};

class List
{
	public:
		//LIST CONSTRUCTOR
		List();

		//DESTRUCTOR
		~List();

		//OVERLOADED << OPERATOR
		friend ostream& operator<<(ostream&, const List&);

		//MODIFICATION MEMBERS
		void insert (const int userID, const string userName, const int userAge);
		void search (const int userID);
		int remove (const int userID);
	private:
		int count;
		Node* head;
		Node* current;
		Node* temp;
};

class dataBase
{
	public:
		
		//constructor 
		dataBase();
		
		//destructor
		~dataBase();
		
		//OVERLOADED << OPERATOR
		friend ostream& operator<<(ostream&, const dataBase&);
		
		//modification members 
		void hash (const int userID, const string userName, const int userAge);
		int remove (const int userID);
		void search(const int userID);
		
	private:
		List arr[5];	
};
#endif
