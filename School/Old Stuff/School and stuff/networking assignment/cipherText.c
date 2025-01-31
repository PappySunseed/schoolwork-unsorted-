#include <time.h>		// Required for random numbers
#include <string.h>		// Required for string reading


void cipherGenerator(char userEntry[]) {

	srand(time(NULL));

	// NUMERIC VARIABLES
	int randomNumberLoop = 0;
	int numberChecker = 0;
	int randomizedNumOne = 0;
	int randomizedNumTwo = 0;
	int translatorNumber = 0;
	int ASCIIcheck = 0;

	int entryLength = strlen(userEntry);

	char translatedMsg[entryLength];
	char holdingVar;

	// Init. as standard ASCII, randomize later; Written this way for readability
	char ASCIIchars[95] = {' ', '!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.',
						   '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
						   '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
						   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']',
						   '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
						   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};

	// Good copy of ASCII for key; DO NOT TOUCH OR ALTER
	char goodASCII[95] = {' ', '!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.',
						   '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
						   '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
						   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']',
						   '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
						   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};

	// RADOMIZES THE ASCII CHARACTER ARRAY
	randomNumberLoop = 0;
	while(randomNumberLoop<95) {
		randomizedNumOne = rand() % 95;
		randomizedNumTwo = rand() % 95;
		while(randomizedNumOne == randomizedNumTwo){
			randomizedNumTwo = rand() % 95;
		}
		holdingVar = ASCIIchars[randomizedNumOne];
		ASCIIchars[randomizedNumOne] = ASCIIchars[randomizedNumTwo];		
		ASCIIchars[randomizedNumTwo] = holdingVar;	
		randomNumberLoop++;
	}
	
	// PRINTS TRANSLATED MESSAGE
	if(entryLength > 0) {
		for(ASCIIcheck = 0; ASCIIcheck < 94; ASCIIcheck++) {
			for(translatorNumber = 0; translatorNumber < 94; translatorNumber++) {
				if(userEntry[ASCIIcheck] == goodASCII[translatorNumber]) {
					translatedMsg[ASCIIcheck] = ASCIIchars[translatorNumber];	
				}
			}	
		}
	}

	for(randomNumberLoop = 0; randomNumberLoop < entryLength; randomNumberLoop++) {
		printf("%c", translatedMsg[randomNumberLoop]);
	}

	// Prints Key
	printf("\n\nKEY;\n");
	for(int i = 0; i < 95; i++) 
		printf("%c = (%c)   ", goodASCII[i], ASCIIchars[i]);

}
