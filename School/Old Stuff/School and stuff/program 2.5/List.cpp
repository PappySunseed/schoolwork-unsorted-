#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "List.h"
#include <string>
#include<limits>
using namespace std;

//BASE CLASS CONSTRUCTOR
//Initialize array size as 2 according to directons.
List::List()
{
	size = 2;		
	count = 0;		
	arrayPtr = new int [size];
}

//BASE CLASS DESTRUCTOR
List::~List()
{
	delete [] arrayPtr;
}

// MODIFICATION MEMBER FUNCTIONS
//List Modification Members
void List::insert(const int userEntry)
{
	string tempString = to_string(userEntry);	
	bool bad;
	
	
	auto found = tempString.find_first_not_of("1234567890");
	
	if(found = std::string::npos)
	{
		bad = false;
	}

	if(bad=true)										
	{
		cout<< "bad data entered. please enter integer"<< endl;
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
	else
	{
		setCount(count);
	
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
}



//sortedList Modification Members
void sortList::insert(const int userEntry)
{	
	int tempStorage;
	
	string tempString = to_string(userEntry);	
	std::size_t found = tempString.find_first_not_of("1234567890");

	if(found!=std::string::npos)										
	{
		
		cout<< "Bad data Detected, Please try again, making sure to only use integers.";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	
	}
	else															
	{
		setCount(getCount());
		
		arrayPtr[getCount() - 1] = userEntry;
	
		//Sorting Code	
	       	for(int j = 1; j < getCount(); j++)
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
	    if(getCount() > 1)
	    {
	    	if (arrayPtr[0] > arrayPtr[1])
			{
				tempStorage = arrayPtr[0];
				arrayPtr[0] = arrayPtr[1];
				arrayPtr[1] = tempStorage;
			}
		}
	}
	
	


}


void List::setCount(const int countEntry)
{
	count = countEntry + 1;
}


// CONSTANT MEMBER FUNCTIONS
//List Constant Member Functions
int List::getCount(void) const
{
	return count;
}


void List::display(void) const
{
	cout << count << " variable(s) inserted.\n" << endl;
	for (int i = 0; i < count; i++)
		cout << arrayPtr[i] << "  " << endl;
}








