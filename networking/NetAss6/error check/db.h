
/*
	COMMENTS FOR FUNCTIONS.
	DO NOT FORGET AGAIN.
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
		void insert (const int userID, const string userName, const int userAge );
		bool search (const int userID);
		int remove (const int userID);
		
	private:
		List arr[5];	
};
#endif
