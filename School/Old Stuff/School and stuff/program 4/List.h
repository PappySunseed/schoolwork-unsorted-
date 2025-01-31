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
//		void setCount (const int countEntry);
//		  Description:		Increases count of times user entered numbers
//		  PreConditions: 	Count data must be appropriate
//		  PostConditions:	Count data is increased and returned
//
// CONSTANT MEMBER FUNCTIONS for the List Class
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
// MODIFICATION MEMBER FUNCTIONS for the sortList Derived Class
//   void insert	 (const int userEntry);
//	 	Description: 	Enters/Sorts user input into dynamic array
//		PreConditions: 	Requires appropriate userEntry
//		PostConditions: Sets appropriate userEntry value equal to array slot
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
    
    //OVERLOADED OPERATORS
    // = Operator
    const List& operator=(const List& orig);

	// + Operator
	friend List operator+(const List&, const List&);
	
	// - Operator
	friend List operator-(List&, const int);
	
	// << Operator
	friend ostream& operator<<(ostream&, List&);

    // MODIFICATION MEMBER FUNCTIONS (setters)
    virtual void insert		(const int userEntry);
	void setCount			(const int countEntry);

    // CONSTANT MEMBER FUNCTIONS (getters)
	int  getCount			(void) const;
	int  getSize			(void) const;
    void display 			(void) const;

  //Protected data, typically for pointers only
  protected:
  	int	*arrayPtr;

  //Hidden data, can only be changed w/ setters
  private:
	int	 size;
	int	 count;
	
};

#endif
