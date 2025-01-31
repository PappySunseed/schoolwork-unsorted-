#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Stack.h"
#include <string>
#include <limits>
#include <cmath>
using namespace std;

// STACK CLASS CONSTRUCTOR
//Initializes head node to safe values; Can eventually be altered based on user entries.
Stack::Stack()
{
	temp = nullptr;
	top = nullptr;
}

// STACK CLASS DESTRUCTOR
Stack::~Stack()
{
    delete top;
	top = nullptr;
	temp = nullptr;
}

// OVERLOADED << OPERATOR
ostream& operator<<(ostream& outp, const Stack& Stack)
{	
	Node *tempCur;		// Exculsively used for reading the stack
	int outputTracker = 0;
	tempCur = Stack.top;

	while(tempCur != nullptr)
	{	
		outp << tempCur->rowNum << tempCur->colNum << tempCur->prevRow << tempCur->prevCol << " ";				//outputs whatever tempCur points to; since this is stack probably should change how this works 
		tempCur = tempCur -> next;
		outputTracker++;
	
		//Only works when outputTracker is perfectly divisible by 5
		//Only 5 entries for every line on display
		if(outputTracker % 5 == 0)
		{
			outp << endl;
			outputTracker = 0;
		}
   
	}
	tempCur = nullptr;
	delete tempCur;
	
	//Occurs when list is empty.
	if (Stack.top == nullptr)
	{
		cout << "Stack is Empty!" << endl;
	}
	
	return outp;
}

// MODIFICATION MEMBER FUNCTIONS
// Push Function
void Stack::push(int rowNum, int colNum, int prevRow, int prevCol) 
{
	
	Node* newNode = new Node;		//creates node 
	
									//data 
	newNode->rowNum = rowNum;
	newNode->colNum = colNum;
	newNode->prevRow = prevRow;
	newNode->prevCol = prevCol;
	
	
	newNode->next = top;			//new nodes next is the current top 
	
	top = newNode;					//moves this node to top of stack

}

// Pop Function
void Stack::pop() 
{
	if(Is_empty())
	{
		return;	
	}	
	
	Node* temp = top;
	
	top = top->next;
	delete temp;
}


// CONSTANT MEMBER FUNCTIONS
// is_Empty Function
bool Stack::Is_empty() const
{
	if(top == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// stack_Top Function
int Stack::Stack_top() const
{
	if (Is_empty() == true)
	{
		cout << "Stack is empty!" << endl;
		return -1;
	}
	else
	{
		return top->rowNum, top->colNum, top->prevRow, top->prevCol;
	}
}



