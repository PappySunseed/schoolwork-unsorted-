#include <stdio.h>
#include <stdlib.h>
#include "cipherText.h"

/*
 * Computer Networking, Lab Assignment 3
 * Caleb Ruby, Caleb Rachocki, Caleb Massey
 * Due 9/21/23
 */
 
// FUNCTIONS 
//void cipherGenerator(char userEntry[]);
 
// MAIN
int main(void) {
	
	// INITIALIZE AND GET OUR USER INPUT
	char userEntry[100];
	printf("Please enter a message:\n> ");
	gets(userEntry);
		
	//This should lead to the most work;
	//We have the cipherGen make everything ONCE, with minimal info provided.
	cipherGenerator(userEntry);

	return 0;
}