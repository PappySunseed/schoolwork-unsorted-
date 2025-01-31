/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/
#ifndef TOKEN_SCANNER
#define TOKEN_SCANNER

#define BUFFER_SIZE 100
#define NUMBER_OF_STRINGS 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_util.h"



int linenumber;
int lexErrs;
int syntErrs;


/**
 * @brief Scans tokens from input file and returns the next token.
 *
 * This function scans tokens from the input file, identifies them, and returns the
 * corresponding enumerated token value. It also outputs the scanned tokens to the list
 * file for reference.
 *
 * @param buffer A character buffer used to store tokens.
 * @param in A pointer to the input file.
 * @param out A pointer to the output file.
 * @param list A pointer to the list file.
 *
 * @return The enumerated value of the next token.
 */
int tokenScanner(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Outputs the scanned token along with its type to the output file.
 *
 * This function prints the scanned token along with its type to the output file.
 * Also formats it across a line, displaying the token number, type, and the actual token received
 * @param buffer The scanned token.
 * @param out A pointer to the output file.
 * @param token The enumerated value of the token.
 */
void outPrint(char* buffer, FILE* out, int token);

/**
 * @brief Clears the contents of a character buffer.
 *
 * This function sets all elements of the character buffer to null characters ('\0'), effectively
 * clearing the contents of the buffer.
 *
 * @param buffer A pointer to the character buffer to be cleared.
 */
void clearBuffer(char* buffer);

/**
 * @brief Adds a character to the end of a character buffer.
 *
 * This function adds a character to the end of a character buffer and updates the null terminator.
 *
 * @param buffer The character buffer.
 * @param c The character to add.
 */
void addChar(char* buffer, char c);

/**
 * @brief Identifies the type of a token.
 *
 * This function identifies the type of a token based on its enumerated value and copies the corresponding
 * token type string into the provided buffer.
 *
 * @param token The enumerated value of the token.
 * @param tokenType A character buffer to store the token type.
 */
void tokenIdentify(int token, char* tokenType);

/**
 * @brief Tests if a token stored in the buffer is a reserved word and returns its enumerated value.
 *
 * This function tests if a token is a reserved word and returns its enumerated value. If the token is not
 * a reserved word, it returns -1.
 *
 * @param buffer containing the token to test.
 *
 * @return The enumerated value of the token if it's a reserved word, otherwise -1.
 */
int reservedTest(char* buffer);



enum token
{
	BEGIN = 1,
	END = 2,
	READ = 3,
	WRITE = 4,
	IF = 5,
	THEN = 6,
	ELSE = 7,
	ENDIF = 8,
	WHILE = 9,
	ENDWHILE = 10,
	ID = 11,
	INTLITERAL = 12,
	FALSEOP = 13,
	TRUEOP = 14,
	NULLOP = 15,
	LPAREN = 16,
	RPAREN = 17,
	SEMICOLON = 18,
	COMMA = 19,
	ASSIGNOP = 20,
	PLUSOP = 21,
	MINUSOP = 22,
	MULTOP = 23,
	DIVOP = 24,
	NOTOP = 25,
	LESSOP = 26,
	LESSEQUALOP = 27,
	GREATEROP = 28,
	GREATEREQUALOP = 29,
	EQUALOP = 30,
	NOTEQUALOP = 31,
	SCANEOF = 32,
	ERROR = 33,
	AND = 34,
	OR = 35
};
#endif
