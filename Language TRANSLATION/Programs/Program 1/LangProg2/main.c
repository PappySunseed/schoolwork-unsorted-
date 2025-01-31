
/*
Group 3 - Language Translation CMSC 4180 001

Program 2 Scanner

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_util.h"
#include "Scanner.h"

int main(int argc, char* argv[])
{
	

	char* tokenBuffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
	char* errList = (char*)malloc(BUFFER_SIZE * sizeof(char));

	char c;

	int totErrors;

	int filesOpen = FileOpen(argc, argv); //initializaiton

	
	int x = tokenScanner(tokenBuffer, errList, in, out, list);;
	while (x != -1 && tokenBuffer != EOF)
	{
		ErrorHandler(tokenBuffer, errList, x);
		x = tokenScanner(tokenBuffer, errList, in, out, list);
		outPrint(tokenBuffer, out, x);
	}

	
	
	

	

	free(tokenBuffer);
	free(errList);
	//closing up 
	if (filesOpen == 0)
	{
		closeFiles();
	}

	return 0;
}