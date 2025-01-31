/*
Group 3 - Language Translation CMSC 4180 001

Program 4 Code Generator

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // Include sys/stat.h for struct stat

//#include "file_util.h"
#include "Scanner.h"
#include "CodeGenerator.h"

int stateFlag = 1;
int stateSucc = 0;
long original_position;
char statementOut[BUFFER_SIZE*3*sizeof(char)];

void printOut(int expected, char* actual, FILE* out)
{
	char* tokenType = (char*)malloc(BUFFER_SIZE * sizeof(char));
	tokenIdentify(expected, tokenType);

	fprintf(list, "%s", actual);
	
		free(tokenType);
}

int system_goal(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{ 
	OpRec opRec;
	ExprRec exprRec;
	


	original_position = ftell(in);
	//printf("\ngoing into program function\n");
	program(buffer, errList, in, out, list);

	
	finish(buffer, out);
	return match(SCANEOF, buffer, errList, in, out, list);
}

int program(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	//printf("\ngoing into start function\n");
	start(buffer, out, outname);

	if (match(BEGIN, buffer, errList, in, out, list) == 0)
	{
		//printf("Error with token: '%s'\n", buffer);
	}
	else
	{
		//printf("Token accepted: '%s'\n", buffer);
		
	}
	
	//printOut(BEGIN, buffer, out);
	//fprintf(out, "\nStatement: %s\n\n\n", statementOut);

	statement_list(buffer, errList, in, out, list);

	if (match(END, buffer, errList, in, out, list) == 0)
	{
		//printf("Error with token: '%s'\n", buffer);
	}
	else
	{

		//printf("Token accepted: '%s'\n", buffer);
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
	//printf("\nMatch value: %d\n", match);
	//printf("input Token value: %d\n", token);
	//printf("input Token llabel: %s\n", tokenLabel);
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
		
		statementOut[0] = '\0';
		stateFlag = statement(buffer, errList, in, out, list);
	} while (stateFlag == 1);
	//statement_list(buffer, errList, in, out, list);
	

}

int statement(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	statementOut[0] = '\0';
	int tokenSwitch = next_token(buffer, errList, in, out, list);
	tempNum = 0;
	


	stateFlag = 1;
	stateSucc = 1;
	//printf("\nNew statement, switching on: %s with value %d\n", buffer, tokenSwitch);
	switch(tokenSwitch)
	{
		case ID:
			//printf("\n	ID case\n");
			if (match(ID, buffer, errList, in, out, list) == 0)
			{
				stateSucc = 0;
				//printf("Semantic error with token '%d'\n", stateSucc);
			}
			else
			{
				//printf("Token matched: '%d', actual token: '%s'\n", stateSucc, buffer);
				strcpy(target.expression, buffer);
				
				
				ident = process_id(buffer, out);
			}
			//printOut(ID, buffer, out);
			if (match(ASSIGNOP, buffer, errList, in, out, list) == 0)
			{
				//printf("Error with statement '%d', read token: '%s'\n", stateSucc, buffer);
			}
			else
			{
				stateSucc = 0;
				//printf("Token matched: '%d', actual token: '%s'\n", stateSucc, buffer);
			}
			//printOut(ASSIGNOP, buffer, out);
			exprBuff2.expression[0] = '\0';
			leftOperand.expression[0] = '\0';
			rightOperand.expression[0] = '\0';
			op.expression[0] = '\0';
			expression(buffer, errList, in, out, list);
			
			
			
			
				//printf("Token accepted: '%s'\n", buffer);
				strcpy(source.expression, leftOperand.expression);
				//assign(source.expression, target.expression, out);
				printf("\n\nTarge expr: %s\tSource Expr: %s", target.expression, source.expression);
				assign(target.expression, source.expression, out);
			
			if (match(SEMICOLON, buffer, errList, in, out, list) == 0)
			{
				stateSucc = 0;

				//printf("Error with statement '%d', read token: '%s'\n", stateSucc, buffer);
			}
			else
			{
				stateSucc = 0;
				//printf("Token matched: '%d', actual token: '%s'\n", stateSucc, buffer);
				printf("\n\nTarge expr: %s\tSource Expr: %s", target.expression, source.expression);
				assign(target.expression, source.expression, out);
			}
			//printOut(SEMICOLON, buffer, out);
			break;
		
		case READ:
			//printf("READ case\n");
			stateSucc = match(READ, buffer, errList, in, out, list);
			stateSucc = match(LPAREN, buffer, errList, in, out, list);

			statementCount = 0;
			id_list(buffer, errList, in, out, list);

			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			match(SEMICOLON, buffer, errList, in, out, list);
			readID(readBuff.expression, out);
			
			break;

		case WRITE:
			//printf("WRITE case\n");
			stateSucc += match(WRITE, buffer, errList, in, out, list);
			stateSucc += match(LPAREN, buffer, errList, in, out, list);

			writeBuff.expression[0] = '\0';
			printCount = 0;
			expr_list(buffer, errList, in, out, list);

			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			stateSucc += match(SEMICOLON, buffer, errList, in, out, list);
			if (stateSucc == 4)
			{
				stateSucc = 1;
			}
			writeExpr(writeBuff.expression, out);
			//printf("\nwritebuffer: %s\n", writeBuff.expression);

			break;
		case IF:
			//printf("IF case\n");
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
			//printf("WHILE case\n");
			stateSucc += match(WHILE, buffer, errList, in, out, list);
			stateSucc += match(LPAREN, buffer, errList, in, out, list);
			condition(buffer, errList, in, out, list);

			//gotta add the conditions in the while statement so they update with each iteration

			stateSucc += match(RPAREN, buffer, errList, in, out, list);
			statement_list(buffer, errList, in, out, list);
			if (match(ENDWHILE, buffer, errList, in, out, list) == 1)
			{
				stateFlag = 1;
			}
			
			break;
		
		default:
			//next statement is not a valid statement or an error 
			//printf("	default case\n");
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
	//printf("\nid_list function");
	int x = match(ID, buffer, errList, in, out, list);
	ident = process_id(buffer, out);
	strcat(readBuff.expression, buffer);
	statementCount++;

	while (next_token(buffer, errList, in, out, list) == COMMA)
	{
		if (next_token(buffer, errList, in, out, list) == COMMA)
		{
			match(COMMA, buffer, errList, in, out, list);
			strcat(readBuff.expression, buffer);
			id_list(buffer, errList, in, out, list);
		}
	} 
	
	return x;
}

int expr_list(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	//printf("\nexpr_list function");
	expression(buffer, errList, in, out, list);
	//strcat(writeBuff.expression, buffer);
	printCount++;

	while (next_token(buffer, errList, in, out, list) == COMMA)
	{
		if (next_token(buffer, errList, in, out, list) == COMMA)
		{
			match(COMMA, buffer, errList, in, out, list);
			
			strcat(writeBuff.expression, buffer);
			expr_list(buffer, errList, in, out, list);
			//printf("\nwritebuffer: %s\n", writeBuff.expression);
			

		}
	}
}

int expression(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	//printf("\nexpression function\n");
	term(buffer, errList, in, out, list); // Parse the first term
	strcat(leftOperand.expression, exprBuff2.expression);
	
	//printf("\nwritebuffer: %s\n", writeBuff.expression);
	int token = next_token(buffer, errList, in, out, list);
	while (token == PLUSOP || token == MINUSOP)
	{
		token = addOp(buffer, errList, in, out, list); // Parse the operator (+ or -)
		term(buffer, errList, in, out, list); // Parse the next term
		strcpy(rightOperand.expression, exprBuff2.expression);
		
		token = next_token(buffer, errList, in, out, list); // Get the next token
	}

	strcpy(leftOperand.expression, genInfix(leftOperand.expression, op.expression, rightOperand.expression, out));
	return 1; // Expression parsed successfully
}


int addOp(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	int swtch = next_token(buffer, errList, in, out, list);
	switch (swtch)
	{
	case PLUSOP:
		if (match(PLUSOP, buffer, errList, in, out, list)) {
			strcat(exprBuffer.expression, buffer);
			strcat(writeBuff.expression, buffer);
			strcpy(op.expression, buffer);
			processOP(op.expression, out);
			return PLUSOP;
		}
	case MINUSOP:
		if (match(MINUSOP, buffer, errList, in, out, list)) {
			strcat(exprBuffer.expression, buffer);
			strcat(writeBuff.expression, buffer);
			strcpy(op.expression, buffer);
			processOP(op.expression, out);
			return MINUSOP;
		}
	}

	return 0;
}

int term(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	//printf("\n	term function");
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
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				strcat(exprBuff2.expression, buffer);
				
				//printf("Token accepted: '%s'\n", buffer);
			}
			factor(buffer, errList, in, out, list);
			strcpy(leftOperand.expression, genInfix(leftOperand.expression, op.expression, rightOperand.expression, out));
			
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
			strcat(buffer, exprBuffer.expression);
			strcpy(op.expression, buffer);
			return MULTOP;
		}
	case DIVOP:
		if (match(DIVOP, buffer, errList, in, out, list)) {
			strcat(buffer, exprBuffer.expression);
			strcpy(op.expression, buffer);
			return DIVOP;
		}
	}
}

int factor(char* buffer, char* errList, FILE* in, FILE* out, FILE* list)
{
	//printf("\n	factor function");
	int y = 0;
	int swtch = next_token(buffer, errList, in, out, list);
	//printf("%s\n", buffer);
	switch (swtch)
	{
		
		case LPAREN:
			y = match(LPAREN, buffer, errList, in, out, list);
			if (y == 0)
			{
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				strcat(exprBuff2.expression, buffer);
				//strcat(writeBuff.expression, buffer);
				//printf("Token accepted: '%s'\n", buffer);
			}
			expression(buffer, errList, in, out, list);
			y = match(RPAREN, buffer, errList, in, out, list);
			if (y == 0)
			{
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				strcat(exprBuff2.expression, buffer);
				//strcat(writeBuff.expression, buffer);
				//printf("Token accepted: '%s'\n", buffer);
			}
			break;

		case MINUSOP:
			y = match(MINUSOP, buffer, errList, in, out, list);
			if (y == 0)
			{
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				strcpy(op.expression, buffer);
				//strcat(writeBuff.expression, buffer);
				//printf("Token accepted: '%s'\n", buffer);
			}
			factor(buffer, errList, in, out, list);
			break;

		case ID:
			y = match(ID, buffer, errList, in, out, list);
			if (y == 0)
			{
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				ident = process_id(buffer, out);
				strcat(exprBuff2.expression, buffer);
				strcat(writeBuff.expression, buffer);
				//printf("Token accepted: '%s'\n", buffer);
			}
			break;

		case INTLITERAL:
			y = match(INTLITERAL, buffer, errList, in, out, list);
			if (y == 0)
			{
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				strcat(exprBuff2.expression, buffer);
				strcat(writeBuff.expression, buffer);
				//printf("Token accepted: '%s'\n", buffer);
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
	//printf("\n	condition function");
	exprBuffer.expression[0] = '\0';
	c_expression(buffer, errList, in, out, list);
	strcpy(leftCond.expression, exprBuffer.expression);
	int token = next_token(buffer, errList, in, out, list);
	while (token == AND || token == OR)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token == AND || token == OR)
		{
			logOp(buffer, errList, in, out, list);
			strcpy(exprBuffer.expression, '\0');
			c_expression(buffer, errList, in, out, list);
			strcpy(rightCond.expression, exprBuffer.expression);
			strcpy(exprBuffer.expression, '\0');

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
	while (token != 0 && token != EOF)
	{
		token = next_token(buffer, errList, in, out, list);
		if (token != 0)
		{
			if (match(token, buffer, errList, in, out, list) == 0)
			{
				//printf("Error with token: '%s'\n", buffer);
				return 0;
			}
			else
			{
				strcat(buffer, exprBuffer.expression);
				//printf("Token accepted: '%s'\n", buffer);
				c_term(buffer, errList, in, out, list);
			}
			
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
			strcpy(op.expression, buffer);
			return LESSEQUALOP;
		}
	case LESSOP:
		if (match(LESSOP, buffer, errList, in, out, list)) {
			strcpy(op.expression, buffer);
			return LESSOP;
		}
	case GREATEREQUALOP:
		if (match(GREATEREQUALOP, buffer, errList, in, out, list)) {
			strcpy(op.expression, buffer);
			return GREATEREQUALOP;
		}
	case GREATEROP:
		if (match(GREATEROP, buffer, errList, in, out, list)) {
			strcpy(op.expression, buffer);
			return GREATEROP;
		}
	case EQUALOP:
		if (match(EQUALOP, buffer, errList, in, out, list)) {
			strcpy(op.expression, buffer);
			return EQUALOP;
		}
	case NOTEQUALOP:
		if (match(NOTEQUALOP, buffer, errList, in, out, list)) {
			strcpy(op.expression, buffer);
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
		strcat(buffer, exprBuffer.expression);
		c_expression(buffer, errList, in, out, list);
		y = match(RPAREN, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		break;

	case MINUSOP:
		y = match(MINUSOP, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		c_primary(buffer, errList, in, out, list);
		break;

	case NOTOP:
		y = match(NOTOP, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		c_primary(buffer, errList, in, out, list);
		break;

	case ID:
		y = match(ID, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		ident = process_id(buffer, out);
		break;

	case INTLITERAL:
		y = match(INTLITERAL, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		break;
	case FALSEOP:
		y = match(FALSEOP, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		break;
	case TRUEOP:
		y = match(TRUEOP, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		break;
	case NULLOP:
		y = match(NULLOP, buffer, errList, in, out, list);
		strcat(buffer, exprBuffer.expression);
		break;

	default:
		//error
		break;

	}
	
	return y;
}



//action variables 
int start(char* buffer, FILE* out, char* outname)
{
	//add header to listing and output files 
	struct stat fileStat;    // Struct to hold file information
	char filepath[150]; // To hold the file path
	//printf("\ninside start function\n");
	// Get file information
	if (fstat(fileno(out), &fileStat) < 0) 
	{
		perror("Error in fstat");
		exit(EXIT_FAILURE);
	}
	if (getcwd(filepath, sizeof(filepath)) == 0) {
		perror("Error getting current working directory");
		exit(EXIT_FAILURE);
	}
	//printf("\nbouta print to file\n");
	// Display file address
	fprintf(out, "/*\nFile Path: %s", filepath);
	//printf("\nyo i just printed the file path to the output file: %s", filepath);
	//printf("\\%s\n", outname);
	fprintf(out, "\\%s\n", outname);
	// Display last modification date
	fprintf(out, "Last modification date: %s */", (char*)ctime(&fileStat.st_mtime));
	//printf("\nand here's the time i just put there: %s\n", (char*)ctime(&fileStat.st_mtime));
	//add C file header information
	fprintf(out, "\n#include<stdio.h>\nmain()\n{\n");

	
	//init symbol table, temp counter, and line counter 
	for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) 
	{
		symbolTable[i][0] = '\0';
	}
//printf("\nproblem here?\n");
	tempCount = 0;	//set tempcount to 0 
	//printf("\nleaving start function\n");
	return 0;
}
int assign(char* leftSide, char* rightSide, FILE* out)
{
	fprintf(temp, "%s = %s;\n", leftSide, rightSide);
}
int openTemp(char* buffer, FILE* out)
{
	//opens second temp file so genInfix also writes a second copy of the expressions to this temnporoary file 
}
int writeTemp(char* buffer, FILE* out)
{
	//appends the temporary file to the code file before the end of the while loop
		///this second copy of the expresions will be sued at the end of the loop so the condition can be updated before the loop returns to the while 
}
int readID(char* expression, FILE* out)
{
	//receives expression record and generates scanf statement
	fprintf(temp, "scanf(\"");
	for (int j = 0; j < statementCount; j++)
	{
		fprintf(temp, "%%d");
	}
	fprintf(temp, "\", %s);\n", readBuff.expression);

	readBuff.expression[0] = '\0';
	statementCount = 0;
}
int writeExpr(char* expression, FILE* out)
{
	fprintf(temp, "printf(\"");

	for (int j = 0; j < printCount; j++)
	{
		fprintf(temp, "%%d");
	}
	fprintf(temp, "\", %s);\n", writeBuff.expression);

	writeBuff.expression[0] = '\0';
	printCount = 0;
	return 0;

}
char* genInfix(char* leftSide, char* operator, char* rightSide, FILE* out)
{
	//create third expression record TEMPEXPR
		//set to new tempID using gettemp

	//generate C code with generate for the assignment of the left expr op with teh right expr to temp file 
	//second copy is written to temp file when opened for the while statemtn 

	char* tempEx = malloc(strlen(leftSide) + strlen(operator) + strlen(rightSide) + 1);
	strcpy(tempEx, leftSide);
	strcat(tempEx, operator);
	strcat(tempEx, rightSide);
	getTemp(tempEx);
	
	("\nTemporary value to be printed to file: %S\n", tempVar);
	fprintf(temp, "%s = %s;\n", tempVar, tempEx);


	leftOperand.expression[0] = '\0';
	op.expression[0] = '\0';
	rightOperand.expression[0] = '\0';

	return tempVar;

	//returns temp expr record r
	
}
int processLiteral(char* buffer, FILE* out)
{
	//creats expr rec LITERALEXPR
		//sets to contents of token buffer (the number)
		//can keep the number as a string 

	//returns the literal expression record 
}
int genCondition(char* condition, FILE* out)
{
	//condition contains left and right side of recrod + contents of relation operation
	//creates C condition without semicolen

	//can contain a single expression
}
ExprRec processOP(char* oper, FILE* out)
{
	//cretes operation record 
		//sets string to type of operation specified
			//may need to translate: ie =, <>, true, and false are not used the same way in C and need to be translated 

	if (strcmp(oper, "=") == 0)
	{
		strcpy(op.expression, "==");
	}
	else if (strcmp(oper, "<>") == 0)
	{
		strcpy(op.expression, "!=");
	}

	return op;
	
}
ExprRec process_id(char* buffer, FILE* out)
{

	strcpy(ident.expression, buffer);

	checkID(buffer, symbolTable);

	return ident;
		
}
int finish(char* buffer, FILE* out)
{
	//printf("\n\n\n\n\n\n\nFinishing UP\n\n\n\n\n\n\n\n\n\n\n\n");

	fclose(temp);
	FILE* tempA = fopen("tempFIle.txt", "r");
	fseek(out, 0, SEEK_END);

	char ch;
	while ((ch = fgetc(tempA)) != EOF) 
	{
		fputc(ch, out);	//places each character from temp to output file 
	}

	fprintf(out, "\nreturn 0;\n}");		//adds closing data to C file as well as error information
		//gotta hadd the errors stuff here

	//still gotta have the listing file stuff 
	
	fclose(tempA);
}

//aditional functions
int lookup(char symbolTable[SYMBOL_TABLE_SIZE][MAX_STR_LENGTH], char* symbol) 
{
	// Iterate through the symbol table
	for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) 
	{
		//printf("\n symbol table entries: %s", symbolTable[i]);
		// Check if the current string is not NULL and matches the search string
		if (symbolTable[i] != NULL && symbolTable[i][0] != '\0')
		{
			//printf("\n symbol table entries: %s", symbolTable[i]);
			if (strcmp(symbolTable[i], symbol) == 0)
			{
				// String found, return its index
				return i;
			}
		}
	}
	// String not found, return 0
	return -1;
}
int enter(char symbolTable[SYMBOL_TABLE_SIZE][MAX_STR_LENGTH], char* symbol)
{
	// Find the first available slot in the symbol table
	for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) 
	{
		// Check if the current slot is empty
		if (symbolTable[i] == NULL || symbolTable[i][0] == '\0')
		{
			// Copy the symbol into the slot
			strcpy(symbolTable[i], symbol);
			return i; // Return the index where the symbol was inserted
		}
	}
	// If the symbol table is full, return -1
	return -1;
}
int checkID(char* ID, char symbolTable[SYMBOL_TABLE_SIZE][MAX_STR_LENGTH])
{
	//use lookup to see if the ID exists and use enter to generate the symbol if it does not 
	if (lookup(symbolTable, ID) == -1)	//if ID not found in symboltable
	{	//then
		fprintf(out, "\nint %s;\n", ID);
		//printf("\nEntered '%s' in symbol table\n", ID);
		return enter(symbolTable, ID);	//enter ID to symbol table
	}
	else
	{
		return -1;
	}
}
int generate(char* codeString) //TODO
{
	//generates code string. Can receive up to five strings and writes them to temp file with ';' at the end 
}
char* getTemp(char* expr) 
{
	char tempHold[20] = { "temp" };

	char intString[20]; // Assuming 20 characters is enough for the integer string representation
	snprintf(intString, sizeof(intString), "%d", tempNum);
	strcat(tempHold, intString);
	//printf("\ntemp num: %d\n", tempNum);

	checkID(tempHold, symbolTable);

	tempNum++; // Increment counter for next temporary ID

	strcpy(tempVar, tempHold);

	return tempVar;
}