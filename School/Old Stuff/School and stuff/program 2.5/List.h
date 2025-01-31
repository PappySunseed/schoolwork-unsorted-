//	CLASS PROVIDED: List
//
// CONSTRUCTOR for the List Class
//	  List()
//		Description: 	Generates safe values for private/protected variables
//		PreConditions: 	N/A
//		PostConditions: Safe values assigned to variables
//
// DESTRUCTOR for the List Class
//	  ~List()
//		Description: 	Frees allocated space
//		PreConditions: 	Program must finish running
//		PostConditions: Freed allocated memory space for dyanmic array
//
// MODIFICATION MEMBER FUNCTIONS for the List Class
//	   void insert	 (const int userEntry);
//		  Description: 		Enters user input into dynamic array
//		  PreConditions: 	Requires appropriate userEntry
//		  PostConditions: 	Sets userEntry value equal to array slot
//
// CONSTANT MEMBER FUNCTIONS for the List Class
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
//
// -----------------------------------------------------------------------------------------
//
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
	void setCount			(const int countEntry);

    // CONSTANT MEMBER FUNCTIONS (getters)
	int  getCount			(void) const;
    void display 			(void) const;

  //Protected data, typically for pointers only
  protected:
  	int	*arrayPtr;

  //Hidden data, can only be changed w/ setters
  private:
	int	 size;
	int	 count;
	
};

class sortList : public List
{
  public:
  	//MODIFICATION MEMBER FUNCTIONS:
  	void insert			(const int userEntry);

};
#endif
