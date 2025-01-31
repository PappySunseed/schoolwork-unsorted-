#include <stdio.h>
#include <string.h>

#define MAX_CHARACTERS 1000


//everything is case sensitive
//the file is formatted very specifically so the sscans know where the different parts of the data are 
//the file is split into 2 parts to be used at differnt times 


int main() {
    FILE *file;
    char filename[50] = {"test.txt"};
    char searchStr[50];						//use username here. We can use this to log into the server as well 				
    char line[MAX_CHARACTERS];
    int line_number = 0;
    
	char newLine[MAX_CHARACTERS];
    char username[50];       
	char name[50];
    char registrationStatus[20];
           
		   
 
//	-1-
// this part of the file simply allows the user to input their username. It searches the local file for said username and returns the data associated there. 
    printf("Enter your username:  ");	//should actually work with real names too, provided they follow the format in the .txt ("_" are important between names)
    fgets(searchStr, 50, stdin);
    searchStr[strcspn(searchStr, "\n")] = 0; 

    file = fopen(filename, "r+"); // Open file in read/write mode

    if (file == NULL) {
        printf("File not found or unable to open the file.\n");
        return 1;
    }

    while (fgets(line, MAX_CHARACTERS, file) != NULL) 
	{
        line_number++;

        if (strstr(line, searchStr) != NULL) 
		{
            printf("User '%s' found: \nName and Registration status: %s\n", searchStr, line);

            char newLine[MAX_CHARACTERS];
            char username[50];
            char name[50];
            char registrationStatus[20];
            break; // Exit the loop after the first match (if you want to update multiple occurrences, remove this)	
					//some of this data is important tho so make sure the variable don't just get overwritten needlessly
        }
    }
//end of part 1. 





//	-2-
//This just changes the unregistered to registered. This function should be used after giving the register command to the server, thus storing locally that this user is registere. 
//Future uses of this program will report this user registered 
	printf("\n\nThis happens after register command is sent.\n\n");	

	sscanf(line, "%s %s %s", username, name, registrationStatus);
	if (strcmp(registrationStatus, "unregistered") == 0) 
	{
        strcpy(registrationStatus, "registered");
        snprintf(newLine, sizeof(newLine), "%s %s %s\n", username, name, registrationStatus);
        fseek(file, -strlen(line), SEEK_CUR); // Move the file pointer to the beginning of the line
        fputs(newLine, file); // Write the modified line back to the file
    }  
    printf("Updated line: %s %s %s\n", username, name, registrationStatus);
//end of part 2 




    fclose(file);
    return 0;
}
