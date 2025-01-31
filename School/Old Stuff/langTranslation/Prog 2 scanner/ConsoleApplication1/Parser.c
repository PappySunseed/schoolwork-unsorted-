/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "file_util.h"
#include "Scanner.h"

int stateFlag = 1;
int stateSucc = 0;
long original_position;
char statementOut[BUFFER_SIZE];

void printOut(int expected, char* actual, FILE* out)
{
	char* tokenType = (char*)malloc(BUFFER_SIZE * sizeof(char));
	tokenIdentify(expected, tokenType);

	fprintf(list, "%s", actual);
	fprintf(out, "Expected Token: %s	Actual Token: %s\n", tokenType, actual);
		free(tokenType);
}

int system_goal(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{ 
	original_position = ftell(in);

	program(buffer, errList, in, out, list);

	

	return match(SCANEOF, buffer, errList, in, out, list);
}

int program(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	

	if (match(BEGIN, buffer, errList, in, out, list) == 0)
	{
		printf("Error with token: '%s'\n", buffer);
	}
	else
	{
		printf("Token accepted: '%s'\n", buffer);
	}
	
	//printOut(BEGIN, buffer, out);
	//fprintf(out, "\nStatement: %s\n\n\n", statementOut);

	statement_list(buffer, errList, in, out, list);

	if (match(END, buffer, errList, in, out, list) == 0)
	{
		printf("Error with token: '%s'\n", buffer);
	}
	else
	{

		printf("Token accepted: '%s'\n", buffer);
	}
	//printOut(END, buffer, out);
	//fprintf(out, "\nStatement: %s\n\n\n", statementOut);
	
}

int match(int token, char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	char* tokenLabel = (char*)malloc(BUFFER_SIZE * sizeof(char));
	tokenIdentify(token, tokenLabel);
	int returnVal = 0;

	int match = tokenScanner(buffer, errList, in, out, list);
	if ( match == token)
	{
		if (ftell(in) != original_position) {
			// Append buffer to statementOut only if the position has changed
			strcat(statementOut, buffer);
			printOut(token, buffer, out);
		}
		original_position = ftell(in);
		
		returnVal = 1;	//true
	}
	if (ftell(in) != original_position) {
		// Append buffer to statementOut only if the position has changed
		linenumber -= 2;
		if (match == 33)
		{
			sprintf(errList + strlen(errList), "Lexical error in line %d: '%s'. Expected '%s'\t", linenumber, buffer, tokenLabel);
			lexErrs++;
		}
		else
		{
			sprintf(errList + strlen(errList), "Syntactic error in line %d: '%s'. Expcted '%s'\t", linenumber, buffer, tokenLabel);
			syntErrs++;
		}
		strcat(errList, "\n");
		linenumber++;
		

		strcat(statementOut, buffer);
		printOut(token, buffer, out);
	}
	original_position = ftell(in);
	free(tokenLabel);
	return returnVal;		//false
}

int next_token(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	long original_position = ftell(in);	//save the original file pointer position


	int nextToken = tokenScanner(buffer, errList, in, out, list); //scanner moving it's postion and whatnot 


	fseek(in, original_position, SEEK_SET);	//restoring file pointer position

	if (nextToken == 33)
	{
		//do some error stuff here 
	}

	return nextToken;
}




int statement_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	
	do
	{
		fprintf(out, "\nStatement: %s\n\n\n", statementOut);
		statementOut[0] = '\0';
		stateFlag = statement(buffer, errList, in, out, list);
	} while (stateFlag == 1);
	//statement_list(buffer, errList, in, out, list);
	

}

int statement(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	statementOut[0] = '\0';
	int tokenSwitch = next_token(buffer, errList, in, out, list);
	
	stateFlag = 1;
	stateSucc = 1;
	printf("\nNew statement, switching on: %s with value %d\n", buffer, tokenSwitch);
	switch(tokenSwitch)
	{
		case ID:
			printf("\n	ID case\n");
			if (match(ID, buffer, errList, in, out, list) == 0)
			{
				stateSucc = 0;
				printf("Semantic error with token '%d'\n", stateSucc);
			}
			else
			{
				printf("Token matched: '%d', actual token: '%s'\n", stateSucc, buffer);
			}
			//printOut(ID, buffer, out);
			if (match(ASSIGNOP, buffer, errList, in, out, list) == 0)
			{
				printf("Error with statement '%d', read token: '%s'\n", stateSucc, buffer);
			}
			else
			{
				stateSucc = 0;
				printf("Token matched: '%d', actual token: '%s'\n", stateSucc, buffer);
			}
			//printOut(ASSIGNOP, buffer, out);
			if(expression(buffer, errList, in, out, list) == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				stateFlag = 0;
			}
			else
			{
				printf("Token accepted: '%s'\n", buffer);
			}
			
			if (match(SEMICOLON, buffer, errList, in, out, list) == 0)
			{
				stateSucc = 0;

				printf("Error with statement '%d', read token: '%s'\n", stateSucc, buffer);
			}
			else
			{
				stateSucc = 0;
				printf("Token matched: '%d', actual token: '%s'\n", stateSucc, buffer);
			}
			//printOut(SEMICOLON, buffer, out);
			break;
		
		case READ:
			printf("READ case\n");
			stateSucc = match(READ, buffer, errList, in, out, list);
			stateSucc = match(LPAREN, buffer, errList, in, out, list);
			id_list(buffer, errList, in, out, list);
			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			stateSucc += match(SEMICOLON, buffer, errList, in, out, list);
			
			break;

		case WRITE:
			printf("WRITE case\n");
			stateSucc += match(WRITE, buffer, errList, in, out, list);
			stateSucc += match(LPAREN, buffer, errList, in, out, list);
			expr_list(buffer, errList, in, out, list);
			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			stateSucc += match(SEMICOLON, buffer, errList, in, out, list);
			if (stateSucc == 4)
			{
				stateSucc = 1;
			}
			
			break;
		case IF:
			printf("IF case\n");
			stateSucc += match(IF, buffer, errList, in, out, list);
			stateSucc += match(LPAREN, buffer, errList, in, out, list);
			condition(buffer, errList, in, out, list);
			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			stateSucc += match(THEN, buffer, errList, in, out, list);
			statement_list(buffer, errList, in, out, list);
			
			if (IFTail(buffer, errList, in, out, list) == 1)
			{
				stateFlag = 1;
			}
			
			
			break;
		case WHILE:
			printf("WHILE case\n");
			stateSucc += match(WHILE, buffer, errList, in, out, list);
			stateSucc += match(LPAREN, buffer, errList, in, out, list);
			condition(buffer, errList, in, out, list);
			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			statement_list(buffer, errList, in, out, list);
			if (match(ENDWHILE, buffer, errList, in, out, list) == 1)
			{
				stateFlag = 1;
			}
			
			break;
		
		default:
			//next statement is not a valid statement or an error 
			printf("	default case\n");
			stateFlag = 0;
	
	}

	
	return stateFlag;
}

int IFTail(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{
		case ELSE:
			match(ELSE, buffer, errList, in, out, list);
			statement_list(buffer, errList, in, out, list);
		case ENDIF:
			return match(ENDIF, buffer, errList, in, out, list);
	}
}


int id_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	printf("\nid_list function");
	int x = match(ID, buffer, errList, in, out, list);

	while (next_token(buffer, errList, in, out, list) == COMMA)
	{
		if (next_token(buffer, errList, in, out, list) == COMMA)
		{
			match(COMMA, buffer, errList, in, out, list);
			id_list(buffer, errList, in, out, list);
		}
	} 
	return x;
}

int expr_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	printf("\nexpr_list function");
	expression(buffer, errList, in, out, list);

	while (next_token(buffer, errList, in, out, list) == COMMA)
	{
		if (next_token(buffer, errList, in, out, list) == COMMA)
		{
			match(COMMA, buffer, errList, in, out, list);
			printOut(COMMA, buffer, out);
			expression(buffer, errList, in, out, list);
		}
	}
}

int expression(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	printf("\n	expression function");
	term(buffer, errList, in, out, list);
	int token = next_token(buffer, errList, in, out, list);
	while (token == PLUSOP || token == MINUSOP)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token == PLUSOP || token == MINUSOP)
		{
			token = addOp(buffer, errList, in, out, list);

			if (match(token, buffer, errList, in, out, list) == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				
				printf("Token accepted: '%s'\n", buffer);
				
			}
			return term(buffer, errList, in, out, list);
		}
	}
	return 0;
}

int addOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{
	case PLUSOP:
		if (match(PLUSOP, buffer, errList, in, out, list)) {
			return PLUSOP;
		}
	case MINUSOP:
		if (match(MINUSOP, buffer, errList, in, out, list)) {
			return MINUSOP;
		}
	}

	return 0;
}

int term(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	printf("\n	term function");
	factor(buffer, errList, in, out, list);
	int token = next_token(buffer, errList, in, out, list);
	while (token == MULTOP || token == DIVOP)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token == MULTOP || token == DIVOP)
		{
			//multOP(buffer, errList, in, out, list);
			if (match(token, buffer, errList, in, out, list) == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);
			}
			return factor(buffer, errList, in, out, list);
		}
	}
}

int multOP(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{
	case MULTOP:
		if (match(MULTOP, buffer, errList, in, out, list)) {
			return MULTOP;
		}
	case DIVOP:
		if (match(DIVOP, buffer, errList, in, out, list)) {
			return DIVOP;
		}
	}
}

int factor(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	printf("\n	factor function");
	int y = 0;
	int swtch = next_token(buffer, errList, in, out, list);
	printf("%s\n", buffer);
	switch (swtch)
	{
		
		case LPAREN:
			y = match(LPAREN, buffer, errList, in, out, list);
			if (y == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);
			}
			expression(buffer, errList, in, out, list);
			y = match(RPAREN, buffer, errList, in, out, list);
			if (y == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);
			}
			break;

		case MINUSOP:
			y = match(MINUSOP, buffer, errList, in, out, list);
			if (y == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);
			}
			factor(buffer, errList, in, out, list);
			break;

		case ID:
			y = match(ID, buffer, errList, in, out, list);
			if (y == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);
			}
			break;

		case INTLITERAL:
			y = match(INTLITERAL, buffer, errList, in, out, list);
			if (y == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);
			}
			break;
		default:
			//error
			y = 0;
			break;

	}
	return y;
}

int condition(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	printf("\n	condition function");
	c_expression(buffer, errList, in, out, list);
	int token = next_token(buffer, errList, in, out, list);
	while (token == AND || token == OR)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token == AND || token == OR)
		{
			logOp(buffer, errList, in, out, list);
			c_expression(buffer, errList, in, out, list);
		}
	}
}

int logOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{
	case AND:
		if (match(AND, buffer, errList, in, out, list)) {
			return AND;
		}
	case OR:
		if (match(OR, buffer, errList, in, out, list)) {
			return OR;
		}
	}
}

int c_expression(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	c_term(buffer, errList, in, out, list);
	int token = relOp(buffer, errList, in, out, list);
	while (token != 0)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token != 0)
		{
			if (match(token, buffer, errList, in, out, list) == 0)
			{
				printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{

				printf("Token accepted: '%s'\n", buffer);

			}
			return c_term(buffer, errList, in, out, list);
		}
	}
	return 0;
}

int relOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{
	case LESSEQUALOP:
		if (match(LESSEQUALOP, buffer, errList, in, out, list)) {
			return LESSEQUALOP;
		}
	case LESSOP:
		if (match(LESSOP, buffer, errList, in, out, list)) {
			return LESSOP;
		}
	case GREATEREQUALOP:
		if (match(GREATEREQUALOP, buffer, errList, in, out, list)) {
			return GREATEREQUALOP;
		}
	case GREATEROP:
		if (match(GREATEROP, buffer, errList, in, out, list)) {
			return GREATEROP;
		}
	case EQUALOP:
		if (match(EQUALOP, buffer, errList, in, out, list)) {
			return EQUALOP;
		}
	case NOTEQUALOP:
		if (match(NOTEQUALOP, buffer, errList, in, out, list)) {
			return NOTEQUALOP;
		}
	}
	return 0;
}


int c_term(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	c_factor(buffer, errList, in, out, list);
	int token = next_token(buffer, errList, in, out, list);
	while (token == PLUSOP || token == MINUSOP)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token == PLUSOP || token == MINUSOP)
		{
			addOp(buffer, errList, in, out, list);
			c_term(buffer, errList, in, out, list);
		}
	}
}

int c_factor(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	c_primary(buffer, errList, in, out, list);
	int token = next_token(buffer, errList, in, out, list);
	while (token == MULTOP || token == DIVOP)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token == MULTOP || token == DIVOP)
		{
			multOP(buffer, errList, in, out, list);
			c_factor(buffer, errList, in, out, list);
		}
	}
}

int c_primary(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int y = 0;
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{

	case LPAREN:
		y = match(LPAREN, buffer, errList, in, out, list);
		c_expression(buffer, errList, in, out, list);
		y = match(RPAREN, buffer, errList, in, out, list);
		break;

	case MINUSOP:
		y = match(MINUSOP, buffer, errList, in, out, list);
		c_primary(buffer, errList, in, out, list);
		break;

	case NOTOP:
		y = match(NOTOP, buffer, errList, in, out, list);
		c_primary(buffer, errList, in, out, list);
		break;

	case ID:
		y = match(ID, buffer, errList, in, out, list);
		break;

	case INTLITERAL:
		y = match(INTLITERAL, buffer, errList, in, out, list);
		break;
	case FALSEOP:
		y = match(FALSEOP, buffer, errList, in, out, list);
		break;
	case TRUEOP:
		y = match(TRUEOP, buffer, errList, in, out, list);
		break;
	case NULLOP:
		y = match(NULLOP, buffer, errList, in, out, list);
		break;

	default:
		//error
		break;

	}
	return y;
}
