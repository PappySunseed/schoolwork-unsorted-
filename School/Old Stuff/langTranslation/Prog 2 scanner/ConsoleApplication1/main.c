/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_util.h"
#include "Scanner.h"
#include "Parser.h"

int main(int argc, char* argv[])
{

	////initialization
	char* tokenBuffer = (char*)malloc(BUFFER_SIZE * sizeof(char));	//buffer passed into scanner 
	char* errList = (char*)malloc(BUFFER_SIZE * sizeof(char));		//buffer for errors in scanner 
	char c;			//character passed in scanner 
	




	int filesOpen = init(argc, argv, errList);
	
	system_goal(tokenBuffer, errList, in, out, list);

	return wrapup(argc, argv, tokenBuffer, errList, filesOpen);
}







int init(int argc, char* argv[], char* errList)
{
	strcpy(errList, "\0");	//initialize errList to empty 

	int filesOpen = FileOpen(argc, argv);

	return filesOpen;
}
int wrapup(int argc, char* argv[], char* tokenBuffer, char* errList, int filesOpen)
{
	free(tokenBuffer);
	free(errList);
	if (filesOpen == 0)
	{
		closeFiles();
	}

	return 0;
}