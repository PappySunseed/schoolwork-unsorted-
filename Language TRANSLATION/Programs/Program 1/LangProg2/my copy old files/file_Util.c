//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "file_util.h"












int hasExt(char* fileName)
{
	int hasExt = 0;

	for (int i = 0; i < strlen(fileName) && !hasExt; i++)
		if (fileName[i] == '.')	//iterates char array until beginning of extension
		{
			hasExt = 1;
		}
	return hasExt;
}

bool validIn(char* fileName)

{
	FILE* f;
	f = fopen(fileName, "r");	//checks if file exists, if not, f = null

	if ((f == NULL))
	{	//case where file doesn't exist 
		printf("Input file cannot be found, input name invalid.\n");
		return false;
	}
	else
	{	//file does exist 
		fclose(f);
		return true;
	}
	
}

bool validOut(char* fileName)	//also use for backup file 
{
	FILE* f;
	f = fopen(fileName, "r");	//checks if file exists, if not, f = null
	if(f != NULL)
	{	//file exists 
		fclose(f);
		printf("Output file of this name found, outputname invalid. Displaying options:\n\n");
		return false;
	}
	else
	{	//file doesn't exist 
		return true;
	}
}

//this needs a file copy function in it 
void createBackup(char* fileName)	//will create a file of the same name with .bak extension. 
{	
	FILE* f;
	strcat(fileName, ".bak"); //adds .bak extension
	f = fopen(fileName, "w"); //creates backup file 

	//copy section; copies from fileName to fileName.bak
}

void createList(char* fileName, FILE* f)
{

}


