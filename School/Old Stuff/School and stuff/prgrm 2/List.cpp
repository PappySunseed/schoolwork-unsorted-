#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "List.h"


//CONSTRUCTOR
//Initialize array size as 2 according to directons.
List::List()
{
	size = 2;		
	count = 0;		
	arrayPtr = new int [size];
}

//COPY CONSTRUCTOR
sortedList::sortedList()
{
	sortsize = 2;
	sortcount = 0;
}

List::~List()
{
	delete [] arrayPtr;	//Destructor works perfectly....
}

sortedList::~sortedList()
{
	delete [] arrayPtr;	//Destructor works perfectly....
}



// MODIFICATION MEMBER FUNCTIONS
void List::insert(const int userEntry)
{
	count++;
		
	if (count == size)
	{
		size = size + 2;
		cout << "Size increased" << endl;
	}	
	arrayPtr[count - 1] = userEntry;
	int	*arrayPtr2 = new int [size];
	
	for (int i = 0; i < count; i++)
	{
		arrayPtr2[i] = arrayPtr[i];
	}
	delete [] arrayPtr;
	
	int	*arrayPtr = new int [size];
	for (int c = 0; c < count; c++)
	{
		arrayPtr[c] = arrayPtr2[c];
	}
	delete [] arrayPtr2;
}


// CONSTANT MEMBER FUNCTIONS
void List::display(void) const
{

	cout << count << " variable(s) inserted.\n" << endl;
	for (int i = 0; i < count; i++)
		cout << arrayPtr[i] << "  " << endl;
}



void sortedList::display(void) const
{
	

	cout << sortcount << " variable(s) inserted.\n" << endl;
	for (int i = 0; i < sortcount; i++)
		cout << arrayPtr[i] << "  " << endl;
		
		
	cout << "array size:" << sortsize;
}



int List::getcount(void) const
{
  return count;
}
int List::getsize(void) const
{
  return size;
}




void sortedList::inserts(const int userEntry)
{
	
	sortcount++;
		
	if (sortcount == sortsize)
	{
		sortsize = sortsize + 2;
		cout << "Size increased" << endl;
	}	
	arrayPtr[sortcount-1] = userEntry;
	int	*arrayPtr2 = new int [sortsize];

	for(int i=0;i<sortcount;i++)
	{
        for(int j=0;j<sortcount-i-1;j--)
		{
			if(arrayPtr[sortcount-1] < arrayPtr[sortcount-2])
			{
				temp = arrayPtr[sortcount-1];
				
				arrayPtr[sortcount-1] = arrayPtr[sortcount-2];
				
				arrayPtr[sortcount-2] = temp;
			}
        }
    }

	for (int i = 0; i < sortcount; i++)
	{
		arrayPtr2[i] = arrayPtr[i];
	}
	delete [] arrayPtr;
	
	int	*arrayPtr = new int [sortsize];
	

	for (int c = 0; c < sortcount; c++)
	{
		arrayPtr[c] = arrayPtr2[c];
	}
	delete [] arrayPtr2;	
	
}






















