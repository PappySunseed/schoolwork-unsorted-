#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 


#define MAX_CHARACTERS 1000
#define RCVBUFSIZE 1024   /* Size of receive buffer */
#define SNDBUFSIZE 1024   /* Size of receive buffer */

char *strupr(char * text)
{
	int i, j=strlen(text);
	
	for (i=0;i<j;i++)
	{
		if ((text[i]>=97)&&(text[i]<=122))
			text[i]=text[i]-32;
	}
	return text;
}

int main(int argc, char *argv[])
{
    int servSock = 0, n = 0;
    char recvBuff[RCVBUFSIZE];
    char recBuffCopy[1024];

    char sendBuff[SNDBUFSIZE];
    char command[20], username[8];
    struct sockaddr_in serv_addr; 
    int quit=0, mistake=0, bytesRcvd;
    char servIP[16];
    int port = 3001;	

	FILE *file;
    char filename[50] = {"test.txt"};
    char line[MAX_CHARACTERS];
    int line_number = 0;
	char newLine[MAX_CHARACTERS];
    char registrationStatus[2];

	// Security Flags
	int encryptMessage = 1;
	int decryptMessage = 0;
	
	// Good copy of ASCII for encrypt/decrypt; DO NOT ALTER
	char goodASCII[95] = {' ', '!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.',
						  '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
						  '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
						  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']',
						  '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
						  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};
	
	// Server team key for encypt/decrypt -- DO NOT ALTER
	char key[95] = {'`', '"', 'G', ')', 'Y', 'F', '7', 'A', ',', 'R', '2', 'L', '\'', '@', ' ', 'Z', 'D', '/', 'E', '5',
					'I', '<', '?', 'H', ':', 'i', '4', 'N', 'J', '&', 'g', ';', 'r', 'B', '(', 'f', '#', 'K', 'o', 'b', 'l',
					'j', 'n', 'W', '1', 'C', '{', '_', '-', 'U', 'a', ']', '%', '^', 'c', 'V', '\\', '>', 't', 'O', 'P', '|',
					'p', 'Q', '$', '6', '8', '9', '=', '+', 'w', 'h', 'z', 'S', '3', '*', 'X', 'm', '!', 'e', 'k', '~', 'M',
					'y', '[', '}', 's', 'q', 'd', 'u', 'v', '0', '.', 'T', 'x'};
		

//User Registration Check
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
            printf("Registration status '0' found in line %d: %s\n You are not currently registered.\n", line_number, line);
            break;
        }
        if (strstr(line, "1") != NULL) {
            printf("Registration status '1' found in line %d: %s\n You are currently registered.\n", line_number, line);
            break;
        }
    }
//end of part 1. 


    strcpy(servIP, "158.83.254.100");             /* First arg: DRACO1 IP address (dotted quad) */

    if((servSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family      = AF_INET;             /* Internet address family */
    serv_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    serv_addr.sin_port        = htons(port); 		 /* Server port */

    if( connect(servSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
            printf("Error: recv() failed or connection closed prematurely\n");      
        
    do
    {
        
		
		//free(translateMsg);        

	printf("----WORKING-----Server_echo:%s \n", translateMsg(recvBuff, goodASCII, key, decryptMessage));
        
        printf("Please type to send to server (type QUIT to quit):");
        scanf("%s", sendBuff);
    
	    if (send(servSock, sendBuff, sizeof(sendBuff), 0) < 0)
	    	printf("Error: send() failed\n");
        
		sleep(1);
    
	    if ( (strcmp (strupr(sendBuff), "QUIT") ==0))
        {
			printf("You have disconnected from the server\n");
            bytesRcvd = 0;
        }                 
	    else
        { 
        	memset(&recvBuff, '0', sizeof(recvBuff)); 
        	if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
            	printf("Error: recv() failed or connection closed prematurely\n");              
            recvBuff[bytesRcvd]='\0';    
        }
        
		if ((strcmp (strupr(sendBuff), "REGISTER") ==0))
        {
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
        }
        
		if ((strcmp (strupr(sendBuff), "MYINFO") ==0))
		{
			char inputString[1024];
			strcpy(inputString,recvBuff);

    		char *namePtr = strstr(inputString, "<User.Name>") + strlen("<User.Name>");
   			char *agePtr = strstr(inputString, "<User.Age>") + strlen("<User.Age>");
   			char *gpaPtr = strstr(inputString, "<User.GPA>") + strlen("<User.GPA>");
    		char *ipPtr = strstr(inputString, "<User.IP>") + strlen("<User.IP>");
		
    		char userName[50];
    		sscanf(namePtr, "%[^<]", userName);

   			int age;
    		sscanf(agePtr, "%d", &age);

			float gpa;
   			sscanf(gpaPtr, "%f", &gpa);

			char userIP[20];
    		sscanf(ipPtr, "%[^<]", userIP);

    		printf("Name: %s\n", userName);
    		printf("Age: %d\n", age);
    		printf("GPA: %.2f\n", gpa);
    		printf("IP: %s\n", userIP);
		}

    } while (bytesRcvd>0);
    
    close(servSock); //close the socket
    return 0;
}
