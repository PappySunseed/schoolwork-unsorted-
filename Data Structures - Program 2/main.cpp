#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "Stack.h"
#include <limits>
#include <cstddef>
#include <string>
#include <cctype>

#define ROWS 11
#define COLUMNS 11

using namespace std;
Stack mainStack;

int arr[ROWS][COLUMNS];

bool vis[11][11] = {false};

void printMaze()
{
	cout << "---- MOUSE MAZE ----" << endl;		
	
	for(int r = 0; r < ROWS; r++) 
	{
		for (int c = 0; c <= COLUMNS; c++) 
			{
				if(c==11)
					cout << "\n";
				if(c < 11)
					cout << arr[r][c] << " ";
			}
	}	
}


//path # function. Got the idea to use a boolean array to keep track of where the mouse was from chatgpt. Prob coulda found a similar idea on stack overflow or smthing tho. 
//To be clear it showed me examples but this is very much my code and took at least an hour to get working right even after seeing it used and discovering the concept
int PathCount(int arr[ROWS][COLUMNS], bool vis[ROWS][COLUMNS], int row, int col)		
{
	if(arr[row][col] == 1 && !vis[row][col])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int main()
{	
	ifstream inputFile;
	string fileName;
	


	// START OF FILE READING.
	inputFile.open("Input.txt");
	cout << "Reading maze data from file . . .\n" << endl;
	if(!inputFile)
	{
		cout << "File not found." << endl;
		exit(1);
	}

	for(int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			inputFile >> arr[r][c];
		}
	}

	inputFile.close();
	// END OF FILE READING
	
	
	printMaze();
	
	//START OF MOUSE FUNCTION 
	int cRow = 5;		//tracks current row 
	int cCol = 0;		//tracks current column
	
	
	//tracks number of available paths the mouse has 
	int Pnum = 0;	
	
	//for picking option 
	int opt1 = 0;
	int opt2 = 0;
	int opt3 = 0;
	int opt4 = 0;
	
	//FIRST MOVE
	cCol++;
	mainStack.push(cRow,cCol,5,0);
	vis[cRow][cCol] = true;
	cout << cRow << ", " << cCol << "\n";
	
	arr[5][0] = 0;	//ensures mouse cannot escape through entrance. shouldn't need but in place just in case 
	
	vis[5][1] = true;
	vis[5][0] = true;
	
	while(cRow != 0 && cRow != 10 && cCol != 0 && cCol != 10 )
	{
		Pnum = PathCount(arr, vis, cRow+1, cCol) + PathCount(arr, vis, cRow-1, cCol) + PathCount(arr, vis, cRow, cCol+1) + PathCount(arr, vis, cRow, cCol-1);
		
		cout << "\n(" << cRow << ", " << cCol << ") Pnum:" << Pnum << "\n";
		
		if(Pnum == 1)
		{
			cout << "case one PNUM = 1\n";
			
			if(PathCount(arr, vis, cRow+1, cCol) == 1)
			{
				cout << "\n" << cRow+1 << ", " << cCol << "\n\n";
				mainStack.push(cRow+1, cCol, 0, 0);
				cRow++;
				
			}
			if(PathCount(arr, vis, cRow-1, cCol) == 1)
			{
				cout << "\n" << cRow-1 << ", " << cCol << "\n\n";
				mainStack.push(cRow-1, cCol, 0, 0);
				cRow--;
			}
			if(PathCount(arr, vis, cRow, cCol+1) == 1)
			{
				cout << "\n"  << cRow << ", " << cCol+1 << "\n\n";
				mainStack.push(cRow, cCol+1, 0, 0);
				cCol++;
			
			}
			if(PathCount(arr, vis, cRow, cCol-1) == 1)
			{
				cout << "\n"  << cRow << ", " << cCol-1 << "\n\n";
				mainStack.push(cRow, cCol-1, 0, 0);
				cCol--;
			}
			vis[cRow][cCol] = true;
		}
	
		if(Pnum > 1)
		{
			
			cout << "case 2 PNUM > 1\n";
			
			mainStack.push(cRow, cCol, mainStack.top->prevRow, mainStack.top->prevCol);
			vis[cRow][cCol] = true;
			
			if(PathCount(arr, vis, cRow+1, cCol) == 1)
			{
				opt4 = 4;
			}
			if(PathCount(arr, vis, cRow-1, cCol) == 1)
			{
				opt3 = 3;
			}
			if(PathCount(arr, vis, cRow, cCol+1) == 1)
			{
				opt2 = 2;
			}
			if(PathCount(arr, vis, cRow, cCol-1) == 1)
			{
				opt1 = 1;
			}
			
			
			if(opt4 > opt3 && opt4 > opt2 && opt4 > opt1)
			{
				if(opt3 == 3)
					mainStack.push(cRow-1, cCol, cRow, cCol);
					cout << "pushed: " << cRow-1 << ","<< cCol << "       ";
				if(opt2 > 0)
					mainStack.push(cRow, cCol+1, cRow, cCol);
					cout << "pushed: " << cRow << ","<< cCol+1 << "       ";
				if(opt1 > 0)
					mainStack.push(cRow, cCol-1, cRow, cCol);
					cout << "pushed: " << cRow << ","<< cCol-1 << "       ";
				cRow++;
				
			}
			else if(opt3 > opt2 && opt3 > opt1)
			{
				if(opt2 > 0)
					mainStack.push(cRow, cCol+1, cRow, cCol);
					cout << "pushed: " << cRow << ","<< cCol+1 << "       ";
				if(opt1 > 0)
					mainStack.push(cRow, cCol-1, cRow, cCol);
					cout << "pushed: " << cRow << ","<< cCol-1 << "       ";
				cRow--;
				

			}
			else if(opt2 > opt1)
			{
				if(opt1 > 0)
					mainStack.push(cRow, cCol-1, cRow, cCol);
					cout << "pushed: " << cRow << ","<< cCol-1 << "       ";
				cCol++;	
				
			}
			else
			{
				cCol--;
			}
			
			cout << "moving to: " << cRow << ", " << cCol << "\n";

			
			mainStack.push(cRow, cCol, 0, 0);
			vis[cRow][cCol] = true;
			
			
			opt1 = 0;
			opt2 = 0;
			opt3 = 0;
			opt4 = 0;
			
			
		}
	
		
		
		
		
		
		if(Pnum == 0)
		{
			cout << "case 3 PNUM = 0\n";
			vis[cRow][cCol] = true;
			
			while(mainStack.top->prevRow == 0 && mainStack.top->prevCol == 0)
			{
				mainStack.pop();
				cout << "POPPED!\n";
				cout << mainStack.top->rowNum << ", " << mainStack.top->colNum << "\n";
				
			}
			
			cRow = mainStack.top->rowNum;
			cCol = mainStack.top->colNum;
			
		
		
				
		}
		
		
	}
	
	

	
	printMaze();
	
	return 0;
}
