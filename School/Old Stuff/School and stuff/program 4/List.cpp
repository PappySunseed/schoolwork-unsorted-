#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "List.h"
#include <string>
#include <limits>
using namespace std;

//BASE CLASS CONSTRUCTOR
//Initialize array size as 5 according to directons.
List::List()
{
	size = 5;		
	count = 0;		
	arrayPtr = new int [size];
}

//BASE CLASS DESTRUCTOR
List::~List()
{
	delete [] arrayPtr;
}

//OVERLOADED OPERATORS
// = Operator
const List& List::operator=(const List& orig)
{ 
	if(this != &orig)
	{
		this->size = orig.size;
		this->count = orig.count;
		delete[] this->arrayPtr;
		this->arrayPtr=new int[orig.size];
		for(int i=0; i<this->size; i++)
		{
			this->arrayPtr[i]=orig.arrayPtr[i];
		}
	}
	return * this;
}

// + Operator
List operator+(const List& List1, const List& List2)
{	
	int totalSize, sizeStorage, sizeStorage2;
	
	//Creates overall size of temporary array.
	sizeStorage = List1.size;
	sizeStorage2 = List2.size;
	totalSize = sizeStorage + sizeStorage2;
	totalSize = totalSize + 5;
	List tempArray;
	int tempArray2[totalSize];
	
	tempArray.size = totalSize;
	
	//Copies list values from List1 into tempArray
	for (int i=0; i>sizeStorage; i++)
	{
		tempArray2[i] = List1.arrayPtr[i];
	}
	
	//Copies list values from List2 into tempArray, picking up where List1 left off.
	for (int j = 0; j>sizeStorage2; j++)
	{
		tempArray2[sizeStorage + j] = List2.arrayPtr[j];
	}
	tempArray.arrayPtr = tempArray2;
	
	return tempArray;
}

// - operator 
List operator-(List& L, const int val) //val is integer to be removed 
{
	List temp;
	
	temp.size = L.size -1;
	
	for(int i=0; i<L.size; i++)
    {
        if(L.arrayPtr[i]==val)
        {
            for(int j=i; j<(L.size-1); j++)
                L.arrayPtr[j] = L.arrayPtr[j+1];
            i--;
        }
    }
    return temp;
}

// << operator
ostream& operator<<(ostream& outp, List& L) 
{
	for (int i = 0; i < L.count; i++)
		outp << L.arrayPtr[i] << "  " << endl;
	return outp;
}

// MODIFICATION MEMBER FUNCTIONS
//List Modification Members
void List::insert(const int userEntry)
{
	string tempString = to_string(userEntry);	
	std::size_t found = tempString.find_first_not_of("1234567890");
	
	if(found!=string::npos)
	{
		cout<< "Bad data Detected, Please try again, making sure to only use integers.";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
	else
	{
		setCount(count);
	
		if (count == size)
		{
			size = size + 5;
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

int List::getSize(void) const
{
	return size;
}








