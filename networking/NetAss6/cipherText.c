#include <stdio.h>
#include <string.h>
#include "cipherText.h"

const char* translateMsg(char message[], char goodASCII[], char key[], int encryptMsg) {
	
	// NUMERIC VARIABLES
	int numberLoop = 0;
	int translatorLoop = 0;
	int ASCIIcheck = 0;

	int msgLength = strlen(message);
	int msgLengthCopy = msgLength;
	

	char* translatedMessage = malloc(msgLength);
	char holdingVar;
	
		while(msgLengthCopy != 0) {
		for(ASCIIcheck = 0; ASCIIcheck < 94; ASCIIcheck++) {
			for(translatorLoop = 0; translatorLoop < 94; translatorLoop++) {
				if(message[ASCIIcheck] == key[translatorLoop] && encryptMsg == 1) {
					translatedMessage[ASCIIcheck] = goodASCII[translatorLoop];
				}
				else if(message[ASCIIcheck] == goodASCII[translatorLoop] && encryptMsg == 0) {
					translatedMessage[ASCIIcheck] = key[translatorLoop];
				}
			}
		}
		msgLengthCopy--;
	}
	
	// Prints our encrypted message
	if(encryptMsg == 0) {
		printf("Encrypted Message:\n");
	}
	else if(encryptMsg == 1) {
		printf("Decrypted Message:\n");
	}
/*
	for(numberLoop = 0; numberLoop < msgLength; numberLoop++) {
		printf("%c", translatedMessage[numberLoop]);
	}
*/

	return translatedMessage;
	
}