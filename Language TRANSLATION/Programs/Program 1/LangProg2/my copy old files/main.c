#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "file_util.h"

int main(int argc, char* argv[])
{
	//initialization
	int parameters = argc - 1;
	bool validInput = 0;
	bool validOutput = 0;
	bool exitProg = 0;

	bool inExist = false;
	bool outExist = false;

	char inName[99];
	char outName[99];
	char temp[99];

	char c[20];

	

	//check for # of paramters from command line;
	if (argc > 1)	//checks for arguemtns 
	{
		strcpy(inName, argv[1]);	//copies arg 1 to input 

		if (!hasExt(inName))
		{
			strcat(inName, ".in");
		}

		if (!validIn(inName))		//validates to confirm input name. if successful, following input loop will be skipped via set of "parameters"
		{
			inName[0] = '\0';
			parameters = 0;
			argc = 0;
		}
		if (argc > 2)	//checks for multiple args. Only checks if there is a valid input parameter 
		{
			strcpy(outName, argv[2]);	//copies 2nd arguement to output
			if (!hasExt(outName))
			{
				strcat(outName, ".out");
			}
			if (!validOut(outName))		//validates output name. if successful, following input loop will be skipped via set of "parameters"
			{
				outName[0] = '\0';
				parameters = 1;
			}
		}
	}
	
	

	//first conditional, occurs if user enters no valid data	(will be skipped if user correctly enters parameters on first try)
	if (parameters == 0)
	{
		printf("Please enter a valid input file name:\n");

		while(!inExist)	//loops until user enters nothing or valid input is given
		{
			scanf(" %s", inName);

			if (!hasExt(inName))
			{
				strcat(inName, ".in");
			}

			if (inName[0] == '\0')	//case to terminate the program 
			{
				printf("No input detected, exiting program...");
				inExist = true;
				exitProg = true;
				outExist = true;
			}

			if (validIn(inName))	//checking validity of input file name 
			{
				inExist = true;
				parameters = 1;
			}
			else	//empties string and re-iterates on invalid entry 
			{
				printf("Invalid input name, please try again.\n");
				inExist = false;
				
			}
		}
	}

	
	if (parameters == 1) //second conditional. Occurs if user enters 1 valid parameter or if the first conditional was successful
	{
		printf("Your input file name has been accepted. Please enter a valid output file name:\n");

		while (!outExist) //loops until a valid output file can be created or a valid choice is made otherwise 
		{
			scanf("%s", outName);
			if (!hasExt(outName))
			{
				strcat(outName, ".out");
			}

			if (validOut(outName))
			{
				outExist = true;
			}
			else
			{
				//fflush(stdin);
				printf("Invalid output name, what would you like to do?\n");
				printf("	1. If you wish to exit, enter 'q' \n");
				printf("	2. Program will default the output filename to '%s'.out if user enters d\n", inName);
				printf("	3. To re-enter the name please  enter 'r' \n");
				printf("	5. To overwrite an existing output file please enter 'o' \n");

				
				
				scanf("%s", &c);
				printf("choice %c\n", c[0]);

				if (c[0] == 'q')	//quit protocol
				{
					outExist = true;
					exitProg = true;
				}
				else if (c[0] == 'd')	//empty return protocol (default filename)
				{
					strcpy(temp, inName);
					strcat(temp, ".out");
					strcpy(outName, temp);
					outExist = true;
				}
				else if (c[0] == 'r')	//re-entry protocol (re-iterates loop)
				{
					outName[0] = '\0';
					outExist = false;
				}
				else if (c[0] == 'o')	//over-wright protocol
				{
					FILE* out = fopen("outName", "w+");
					outExist = true;
				}
				else	//case for invalid selection from dialogue menu 
				{
					printf("Invalid selection, restarting output name selection process:\n");
					outName[0] = '\0';
					outExist = false;
				}
			}
		}
	}
		
		
				
			
	if (!exitProg)
	{
	//body of program goes here - fileOpen Routine
		printf("File Open routine starting:\n");
/*
		ext = strrchr(inName, '.');
		if (!ext) {
			ext = 
		}
		else {
			printf("extension is %s\n", ext + 1);
		}
*/
		//create outName.extension
		//create temp.txt
		//create list file (outName.lis)

		//open all files using fileopen()
			//return code for success/fail for each

		//read char by char from input file

		//write contents of input file in output, list, and temp files 

		//code to delete the temp file, commented out 
		/*
		*/
	
			
		return 0;
	}
	else if (exitProg)
	{
		printf("\n exit protocol");
		return 0;
	}

}