/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_util.h"

#ifndef PARSER_H
#define PARSER_H





/**
 * @brief Prints the expected and actual tokens to the output file.
 *
 * This function prints the expected and actual tokens to the output file.
 *
 * @param expected The expected token value.
 * @param actual The actual token value stored in the buffer.
 * @param out The output file pointer.
 */
void printOut(int expected, char* actual, FILE* out);

/**
 * @brief Parses the system goal non-terminal symbol.
 *
 * This function parses the system goal non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int system_goal(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the program non-terminal symbol.
 *
 * This function parses the program non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 */
int program(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Matches the current token with the expected token.
 *
 * This function matches the current token with the expected token.
 *
 * @param token The expected token value.
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if tokens match, 0 otherwise.
 */
int match(int token, char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Retrieves the next token from the input file.
 *
 * This function retrieves the next token from the input file.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return The token value of the next token.
 */
int next_token(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the statement list non-terminal symbol.
 *
 * This function parses the statement list non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 */
int statement_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the statement non-terminal symbol.
 *
 * This function parses the statement non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int statement(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the IFTail non-terminal symbol.
 *
 * This function parses the IFTail non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int IFTail(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the id list non-terminal symbol.
 *
 * This function parses the id list non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int id_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);




/**
 * @brief Parses the expression list non-terminal symbol.
 *
 * This function parses the expression list non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 */
int expr_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the expression non-terminal symbol.
 *
 * This function parses the expression non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int expression(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the add operation non-terminal symbol.
 *
 * This function parses the add operation non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return The add operation token if parsing is successful, otherwise 0.
 */
int addOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the term non-terminal symbol.
 *
 * This function parses the term non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int term(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the multiplication operation non-terminal symbol.
 *
 * This function parses the multiplication operation non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return The multiplication operation token if parsing is successful, otherwise 0.
 */
int multOP(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);


/**
 * @brief Parses the factor non-terminal symbol.
 *
 * This function parses the factor non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int factor(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the conditional expression non-terminal symbol.
 *
 * This function parses the conditional expression non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int c_expression(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the relational operation non-terminal symbol.
 *
 * This function parses the relational operation non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return The relational operation token if parsing is successful, otherwise 0.
 */
int relOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the logical operation non-terminal symbol.
 *
 * This function parses the logical operation non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return The logical operation token if parsing is successful, otherwise 0.
 */
int logOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the conditional term non-terminal symbol.
 *
 * This function parses the conditional term non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int c_term(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the conditional factor non-terminal symbol.
 *
 * This function parses the conditional factor non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int c_factor(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the conditional primary non-terminal symbol.
 *
 * This function parses the conditional primary non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int c_primary(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);

/**
 * @brief Parses the condition non-terminal symbol.
 *
 * This function parses the condition non-terminal symbol.
 *
 * @param buffer The buffer to store the current token.
 * @param errList The buffer to store error messages.
 * @param in The input file pointer.
 * @param out The output file pointer.
 * @param list The list file pointer.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int condition(char* buffer, char* errList, FILE* in, FILE* out, FILE* list);


#endif /* PARSER_H */



