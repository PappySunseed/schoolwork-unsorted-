#include <stdio.h>
#include <string.h>

#define MAX_CHARACTERS 1000


//the file is split into 2 parts to be used at differnt times 
int main() {
    FILE *file;
    char filename[50] = {"test.txt"};
    char line[MAX_CHARACTERS];
    int line_number = 0;
    
	char newLine[MAX_CHARACTERS];
    char registrationStatus[2];

//	-1-
// this part of the file checks local file for a 0 or a 1. It breaks after either is found so you have the "line_number" saved and that can be used later if need be 
	//also opens the file VVV
    file = fopen(filename, "r+"); // Open file in read/write mode
    if (file == NULL) {
        printf("File not found or unable to open the file.\n");
        return 1;
    }

	//the checking part 
    while (fgets(line, MAX_CHARACTERS, file) != NULL) {
        line_number++;

        // Check if the string "0" is present in the line
        if (strstr(line, "0") != NULL) {
            printf("Registration status '0' found in line %d: %s\n You are not currently registered.", line_number, line);
            break;
        }
        if (strstr(line, "1") != NULL) {
            printf("Registration status '1' found in line %d: %s\n You are currently registered.", line_number, line);
            break;
        }
    }
//end of part 1. 





//	-2-
//This just changes the unregistered to registered. This function should be used after giving the register command to the server, thus storing locally that this user is registered. 
//Future uses of this program will report this user registered so long as the the test.txt is unchanged. The assumption is that this is local storage for a single user 
//essentially this will track whether the user has logged in already or not 
//
	//just some clarification while running 
	printf("\n\n\n\n\n\nThis happens after register command is sent. \n| | |\nV V V\n\n");	

	//searches at the stored spot 'line' that the 0 was found at 
	sscanf(line, "%s" , registrationStatus);
	if (strcmp(registrationStatus, "0") == 0) 	//conditional making sure there was a 0 there in case something got wonky
	{
        strcpy(registrationStatus, "1");	//makes a string copy with updated data
        snprintf(newLine, sizeof(newLine), "%s\n", registrationStatus);	//makes a new line
        fseek(file, -strlen(line), SEEK_CUR); // Move the file pointer to the beginning of the line
        fputs(newLine, file); // Write the modified line back to the file
        printf("Updated Registration Status: %s\n", registrationStatus);
    }  
//end of part 2 




    fclose(file);
    return 0;
}
