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
		N/A
		
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
		
-------------------------------------------------------------------------------------------------*/

#ifndef STACK_H
#define STACK_H
#include <cstdlib>

using namespace std;

struct Node
{
	int rowNum;
	int colNum;
	int prevRow;
	int prevCol;
	
	Node* next;
	
};


class Stack
{
	public:
		//STACK CONSTRUCTOR
		Stack();

		//DESTRUCTOR
		~Stack();

		//OVERLOADED << OPERATOR
		friend ostream& operator<<(ostream&, const Stack&);

		//MODIFICATION MEMBERS
		void push (int rowNum, int colNum, int prevRow, int prevCol);
		void pop ();
		
		//CONSTANT MEMBER
		int Stack_top() const;
		bool Is_empty() const;
		Node* top;
		

	private:
		int count;
		Node* temp;
		
};

#endif
