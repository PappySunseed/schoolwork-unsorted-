/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/
#include <stdio.h>
#include <string.h>
#include "file_util.h"


int FileOpen(int argc, char* argv[])
{
//initialization
	int parameters = argc - 1;

	int validInput;
	validInput = -1;

	int validOutput;
	validOutput = -1;

	int exitProg;
	exitProg = -1;

	int inExist;
	inExist = -1;

	int outExist;
	outExist = -1;

	int overWrite;
	overWrite = -1;

	int i;

	char inFile[99];
	char outFile[200];
	char listFile[200];
	char bakFile[99];
	char tempFile[99] = "tempFile_WhichHasNameNoOneWillUse_";

	char holding[99];
	char c;


	

	//check for # of paramters from command line;
	if (argc > 1)	//checks for arguemtns 
	{
		strcpy(inFile, argv[1]);	//copies arg 1 to input 

		

		if (validIn(inFile) == -1)		//validates to confirm input name. if successful, following input loop will be skipped via set of "parameters"
		{
			inFile[0] = '\0';
			inExist = -1;
		}
		else
		{
			inExist = 1;
			strcpy(outFile, inFile);

			if (hasExt(inFile) != 1)
			{
				strcat(inFile, ".in");
			}
			
		}
		
	}

	//first conditional, occurs if user enters no valid data	(will be skipped if user correctly enters parameters on first try)
	if (inExist == -1)
	{
		printf("----Program will create directory 'OUTPUT_FILES' in which the listing and output files will be placed for ease of use----\n");

		printf("\nPlease enter a valid input file name:\n");

		while (inExist == -1)	//loops until user enters nothing or valid input is given
		{

			fgets(inFile, 99, stdin);
			//scanf("%s", inFile);

			
			if (inFile[0] == '\n')	//case to terminate the program 
			{
				printf("No input detected, exiting program...");
				inExist = 1;
				exitProg = 1;
				outExist = 1;
			}

			if (exitProg != 1)
			{
				for (i = 0; i < strlen(inFile); i++)
				{
					if (inFile[i] == ' ' || inFile[i] == '\n' || inFile[i] == '\r')	//iterates char array until string is over 
					{
						inFile[i] = '\0';
						i = strlen(inFile);

					}
				}
			}
			
			printf("You entered %s\n", inFile);
			if (validIn(inFile) == 1)	//checking validity of input file name 
			{
				inExist = 1;
				printf("%s is a valid input file\n", inFile);

				strcpy(outFile, inFile);

				if (hasExt(inFile) != 1)
				{
					strcat(inFile, ".in");
				}
				
			}
			else if (exitProg != 1)	//empties string and re-iterates on invalid entry 
			{
				printf("Invalid input name, please try again.\n");
				inFile[0] = '\0';
			}
		}
	}

	if (exitProg == -1)
	{
		//body of program goes here - fileOpen Routine
		printf("File Open routine starting:\n");

		//create list file (outName.lis)
		strcpy(listFile, outFile);
		if (hasExt(listFile) == 1)
		{
			for (i = strlen(listFile); i > 0; i--)
			{
				if (listFile[i] == '.')	//iterates char array until beginning of extension
				{
					listFile[i] = '\0';
				}
			}
		}

		if (hasExt(outFile) == 1)
		{
			for (i = strlen(outFile); i > 0; i--)
			{
				if (outFile[i] == '.')	//iterates char array until beginning of extension
				{
					outFile[i] = '\0';
				}
			}
		}
		strcat(outFile, ".c");
		strcat(listFile, ".lis");

		//open all files using fileopen()
		//return code for success/fail for each

		if (overWrite == 1)
		{
			strcat(bakFile, ".bak");

			bak = fopen(bakFile, "w");
			isOpen(bak);

			out = fopen(outFile, "r");
			isOpen(out);

			fileCopy(out, bak);

			fclose(bak);
			fclose(out);
		}

		//open files, get success or failure message 
		printf("%s\n", inFile);
		in = openFile(inFile, "r");

		createFilesInDirectory(outFile, listFile);
		char cwd[1024];
		char tempDir[1024];
		strcpy(tempDir, getcwd(cwd, sizeof(cwd)));
		strcat(tempDir, "\\OUTPUT_FILES");

		strcat(tempDir, "\\");
		strcat(tempDir, outFile);
		strcpy(outFile, tempDir);

		strcpy(tempDir, getcwd(cwd, sizeof(cwd)));
		strcat(tempDir, "\\OUTPUT_FILES");

		strcat(tempDir, "\\");
		strcat(tempDir, listFile);
		strcpy(listFile, tempDir);
		


		out = openFile(outFile, "w");

		list = openFile(listFile, "w");

		temp = openFile("tempFIle.txt", "w");

		temp2 = openFile("tempFIleNumero_2_.txt", "w");

		/*//read char by char from input file
		fileCopy(in, out);
		fileCopy(in, list);
		fileCopy(in, temp);
		fileCopy(in, temp2);
		*/
		return 0;
	}
	else
	{
		return -1;
	}
}

void createFilesInDirectory(const char* outFile, const char* listFile)
{
	// Create directory if it doesn't exist
	if (mkdir("OUTPUT_FILES") == -1) {
		// Directory already exists or creation failed
		// Check if error is due to directory already existing
		if (errno != EEXIST) {
			perror("Error creating directory");
			exit(EXIT_FAILURE);
		}
	}
	return;
}


FILE* openFile(char* filename, char* fileMode)
{
	//char tempName[99];
	FILE* F = fopen(filename, fileMode);
	isOpen(F);
	return F;
}
void closeFiles()
{
	if (in != NULL)
	{
		fclose(in);
	}
	if (out != NULL)
	{
		fclose(out);
	}
	if (list != NULL)
	{
		fclose(list);
	}
	if (temp != NULL)
	{
		fclose(temp);
	}
	if (temp2 != NULL)
	{
		fclose(temp2);
	}

	return;
}
int isOpen(FILE* f)
{

	if (f == NULL)	//method discoevered at https://stackoverflow.com/questions/14680232/how-to-detect-a-file-is-opened-or-not-in-c
	{
		printf("fileOpen of %s failed: return value -1\n", f);

		return -1;
	}
	else
	{
		printf("fileOpen of %s successful: return value 0\n", f);

		return 1;
	}
}


int hasExt(char* fileName)
{
	int hasExt = -1;

	int i;

	for (i = strlen(fileName); i > 0 && hasExt != 1; i--)
	{
		if (fileName[i] == '.')	//iterates char array until beginning of extension
		{
			hasExt = 1;
		}
	}

	return hasExt;
}

int validIn(char* fileName)

{
	FILE* f;
	f = fopen(fileName, "r");	//checks if file exists, if not, f = null

	if (f == NULL)
	{	//case where file doesn't exist 
		printf("Input file cannot be found, input name invalid.\n");
		return -1;
	}
	else
	{	//file does exist 
		fclose(f);
		return 1;
	}

}

int validOut(char* fileName)	//also use for backup file 
{
	FILE* f;
	f = fopen(fileName, "r");	//checks if file exists, if not, f = null
	if (f != NULL)
	{	//file exists 
		fclose(f);
		printf("Output file of this name found, outputname invalid. Displaying options:\n\n");
		return -1;
	}
	else
	{	//file doesn't exist 
		strcpy(outname, fileName);
		return 1;
	}
}


void fileCopy(FILE* src, FILE* dest)
{
	printf("\nfile copy started\n");
	char c = fgetc(src);
	while (c != EOF)
	{
		fputc(c, dest);
		c = fgetc(src);
	}

	rewind(src);
	return;
}
