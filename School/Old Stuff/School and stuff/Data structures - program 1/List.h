

//***REMEMBER TO ADD COMMENTS FOR FUNCTION WHEN COMPLETED***

#ifndef LIST_H
#define LIST_H
#include <cstdlib>

using namespace std;

struct Node
{
	int storedNum;
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
		void insert (const int entry);	//Reads user entry, throws it in new node, adds node to LL
		bool search (const int entry);	//Reads user entry, searches for it in the array; must return true/false val if found
		int  remove (void);				//Removes the node found via search function... Pointers should already be set?
		int errorCheckingInt(string &entry);




		
		
	

	
	private:
		int count;
		Node* head;
		Node* current;
		Node* temp;
};

#endif
