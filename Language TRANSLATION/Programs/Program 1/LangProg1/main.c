/*
Group 3 - Language Translation CMSC 4180 001

Program 1 fileOpen Routine

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/

#include <stdio.h>
#include <string.h>
#include "file_util.h"
#include "Scanner.h"




int main(int argc, char* argv[])
{

	int filesOpen = FileOpen(argc, argv); //initializaiton

	
	



	//closing up 
	if (filesOpen == 0)
	{
		closeFiles();
	}

	return 0;
}