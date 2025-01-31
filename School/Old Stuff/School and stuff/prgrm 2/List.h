//	CLASS PROVIDED: List
//
// CONSTRUCTOR for the List Class
//	  List()
//		Description:
//		PreConditions:
//		PostConditions:
//
//	MODIFICATION MEMBER FUNCTIONS for the List Class
//		void setSize (const int userSize);
//		  Description: 		Sets the size of the array
//		  PreConditions: 	Requires user input from userSize variable
//		  PostConditions: 	Sets newSize value equal to size
//
//		void setCount (const int counterVar);
//		  Description:		Sets the count (???)
//		  PreConditions:	Requires counterVar to be used (??)
//		  PostConditions: 	Sets counterVar value equal to count
//
//		void insert (const int entry);
//		  Description:		Allows user to insert new number
//		  PreConditions:	Array must not be full, value must be appropriate
//		  PostConditions:	Enters new entry into array
//
//	CONSTANT MEMBER FUNCTIONS for the List Class
//		int getSize (void) const;
//		  Description:		Obtains the size of the array
//		  PreConditions: 	Size data must be appropriate
//		  PostConditions:	Size data is returned
//
//		int getCount (void) const;
//		  Description: 		Obtains the count (??)
//		  PreConditions: 	Count data must be appropriate
//		  PostConditions:	Count data is returned
//
//		void display (void) const;
//		  Description: 		Displays all required information
//		  PreConditions: 	All private data values must be acceptable
//		  PostConditions:	Array values are displayed on screen
//	CLASS PROVIDED: sortList
//






// DEFAULT CONSTRUCTOR for the sortList Derived Class
//   sortList() : List()
//		Description: 	Creates initial safe values for private derived class data.
//		PreConditions: 	N/A
//		PostConditions: Safe values for private DC data created
//
// COPY CONSTRUCTOR for the sortList Derived Class
//   sortList(const List &baseData);
//		Description: 	Generates safe values for private/protected variables
//		PreConditions: 	N/A
//		PostConditions: Safe values assigned to variables
//
// DESTRUCTOR for the sortList Derived Class
//   ~sortList()
//		Description: 	Frees allocated space
//		PreConditions: 	Program must finish running
//		PostConditions: Freed allocated memory space for dyanmic array
//
// MODIFICATION MEMBER FUNCTIONS for the sortList Derived Class
//   void insert	 (const int userEntry);
//	 	Description: 	Enters/Sorts user input into dynamic array
//		PreConditions: 	Requires appropriate userEntry
//		PostConditions: Sets appropriate userEntry value equal to array slot
//
// CONSTANT MEMBER FUNCTIONS for the sortList Derived Class
//   void display (void) const;
//		Description: 	Displays all required information
//		PreConditions: 	All private data values must be acceptable
//		PostConditions:	Sorted array values are displayed on screen
//

#ifndef LIST_H
#define LIST_H
#include <cstdlib>

using namespace std;

class List
{
  //Public data, can be used/altered with setters and getters
  public:
    // CONSTRUCTOR
    List();
    
    //DESTRUCTOR
    ~List();
    
    //Not sure if we include the Copy Constructor in this class, or the derived class...

    // MODIFICATION MEMBER FUNCTIONS (setters)
    void insert				(const int userEntry);

    // CONSTANT MEMBER FUNCTIONS (getters)
    void display 			(void) const;
	int		 getcount		(void) const;
 	int		 getsize		(void) const;

  //Protected data, typically for pointers only
  protected:
  	int	*arrayPtr = new int;

  //Hidden data, can only be changed w/ setters
  private:
	int	 size;
	int	 count;
	
};

class sortedList : public List
{
  //Public data
  public:
  	
	sortedList();
	
	~sortedList();
  
	//MODIFICATION MEMBER FUNCTIONS (setters)
    void inserts				(const int userEntry);
    void display 			(void) const;
private:
	
	int sortsize = 2;
	int sortcount = 0;
	int temp;


};

#endif
