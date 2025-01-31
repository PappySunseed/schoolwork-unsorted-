#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "List.h"

using namespace std;

//BASE CLASS CONSTRUCTOR
//Initialize array size as 2 according to directons.
List::List()
{
	size = 2;		
	count = 0;		
	arrayPtr = new int [size];
}

//DERIVED CLASS COPY CONSTRUCTOR
sortList::sortList(const List &baseData)
{
	size = baseData.getSize();
	count = baseData.getCount();
}

//BASE CLASS DESTRUCTOR
List::~List()
{
	delete [] arrayPtr;
}

//DERIVED CLASS DESTRUCTOR
sortList::~sortList()
{
	delete [] arrayPtr;
}

// MODIFICATION MEMBER FUNCTIONS
//List Modification Members
void List::insert(const int userEntry)
{
	count++;
		
	if (count == size)
	{
		size = size + 2;
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



//sortedList Modification Members
void sortList::insert(const int userEntry)
{	
	int tempStorage;
	int	*arrayPtr2 = new int [size];
	int i;
	count++;
	
	//Sorting Code


	arrayPtr[count - 1] = userEntry;
	
	if (userEntry < arrayPtr[count - 2])
	{
       	for(int j = 1; j < count; j++)
		{
			if(arrayPtr[j] < arrayPtr[j - 1])
			{
				tempStorage = arrayPtr[j];
				arrayPtr[j] = arrayPtr[j - 1];
				arrayPtr[j - 1] = tempStorage;
				
				if (j > 1)
					if (arrayPtr [j - 1] < arrayPtr[j - 2])
					{
						tempStorage = arrayPtr[j - 1];
						arrayPtr[j - 1] = arrayPtr[j - 2];
						arrayPtr[j - 2] = tempStorage;
					}
				
			}
        }
	}
	
/*	if (userEntry < arrayPtr[count - 2])		
	{

		for (i = 0; i < count - 1; i++)
		{
			cout << "I suck lol" << endl;
			tempStorage = arrayPtr[i];
			arrayPtr[i - 1] = tempStorage;
			arrayPtr[count - 1] = userEntry;
		}
	}
	else
	{
		arrayPtr[count - 1] = userEntry;
	}*/
	
	//Size Increase Code
	if (count == size)
	{
		size = size + 2;		
		
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
	
	/*
	
	arrayPtr[count - 1] = userEntry;
		for (i = 0; i < count - 1; i++)
			tempStorage = arrayPtr[i];
			arrayPtr[i - 1] = tempStorage;
			arrayPtr[count - 1] = userEntry;

	*/
}
/*	
	for(int i = 0; i < getCount(); i++)
	{
        for(int j = 0; j < getCount() - i - 1; j--)
		{
			if(arrayPtr[getCount() - 1] < arrayPtr[getCount() - 2])
			{
				tempStorage = arrayPtr[getCount() - 1];
				
				arrayPtr[getCount() - 1] = arrayPtr[getCount() - 2];
				
				arrayPtr[getCount() - 2] = tempStorage;
			}
        }
    }
*/




// CONSTANT MEMBER FUNCTIONS
//List Constant Member Functions
int List::getCount(void) const
{
	return count;
}

int List::getSize(void) const
{
	return size;
}

void List::display(void) const
{
	cout << count << " variable(s) inserted.\n" << endl;
	for (int i = 0; i < count; i++)
		cout << arrayPtr[i] << "  " << endl;
}


//sortedList Constant Member Functions
void sortList::display() const
{
	cout << count << " variable(s) inserted.\n" << endl;
	for (int i = 0; i < count; i++)
		cout << arrayPtr[i] << "  " << endl;
}























