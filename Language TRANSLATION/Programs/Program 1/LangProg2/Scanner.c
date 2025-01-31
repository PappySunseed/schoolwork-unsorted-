/*
Group 3 - Language Translation CMSC 4180 001

Program 2 Scanner

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/
#include "Scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"

int linenumber = 0;
int startofline;
char c;
int tokenScanner(char* buffer, char* errList, FILE* in, FILE* out, FILE* list) //returns the enumerated next token 
{
    int ascii;

    clearBuffer(buffer);   //clear input buffer 


    c = fgetc(in);
    if (c == '\n') {
        startofline = 1; // Set startofline flag for the next line
    }
    if (c == EOF)
    {
        return -1;
    }
    while (c != EOF)  //read from input file 
    {
        if (c == '\n') {
            startofline = 1; // Set startofline flag for the next line
        }
        if (startofline) 
        {
            fprintf(list, "%d.  ", ++linenumber); // Output line number at the beginning of a line
            startofline = 0; // Reset startofline flag
        }
        if (c == '\n') {
            startofline = 1; // Set startofline flag for the next line
        }
        if (startofline == 1 && errList[0] != '\0')
        {
            startofline = 0;
            linenumber--;
            fprintf(list, "\nErrors(s) found: %s unrecognized.\n", errList);
            clearBuffer(errList);
        }
       

       //consume whitespace
        while (c == ' ' || c == '\t')
        {
            c = fgetc(in);
        }
        
        ascii = (int)c; //converts c to ascii value
        
        //need to check if first char is alphabet first, to see if variable name basically
        if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))// || (ascii > 47 && ascii < 58))     //if the ASCII value of c is within the alphabet values 
        {
            int i = 0;  //local counter for buffer[]
        
            while ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123) || (ascii > 47 && ascii < 58)) //copies whole string of letters/numbers after first alpha char
            {
                fputc(c, list); //place char in list file
                buffer[i] = c;  //places char in token buffer

                c = fgetc(in);  //advance next char from 'in'
                ascii = (int)c; //get ascii value for next char
                i++;            //advanced for token buffer 
            }

            //***at this point the entire alphanumeric string has been read and saved***

            if(reservedTest(buffer) > 0)
            {
                    //outPrint(buffer, out, isReserved(buffer));
                return reservedTest(buffer);
            }
            else
            {
                    //outPrint(buffer, out, ID);
                return ID;
            }
        }
        else if (c == '-')
        {
            char hold = c;  //save value of c (should be '-')

            c = fgetc(in);  //advance to next char in file, place in "c"
            ascii = (int)c;
            if (c == '-')//if there are two "-" next to eachother, signaling a line comment 
            {
                fputc(hold, list); //places the first '-' in the list file. Seoncd minus will be placed on first iteration of loop 
                while (c != '\n' && c != EOF) //consumes characters until a new line or EOF 
                {
                    fputc(c, list);
                    c = fgetc(in);
                }
            }
            else if ((ascii > 47 && ascii < 58))    //if char after '-' is a digit 
            {
                int i = 0; //for buffer[]                        
                buffer[i] = hold;   //places '-' in buffer

                fputc(hold, list); //place first '-' in list file
                while ((ascii > 47 && ascii < 58))   //reads all consecutive digits 
                {
                    fputc(c, list); //place char in list file
                    buffer[i] = c;  //places digit in token buffer

                    c = fgetc(in);  //advance next char from 'in'
                    ascii = (int)c; //get ascii value for next char
                    i++;            //advanced for token buffer
                }

                //token buffer now contains an INTLITERAL  
                    //outPrint(buffer, out, ID);  //places this int literal into output file as token type ID
                return ID;
            }
            else //when the char after '-' isn't a digit or a second '-' it will now be treated as a minus operator 
            {
                buffer[0] = hold;   //places what should be '-' in buffer
                fseek(in, -1, SEEK_CUR);    //"puts" the char after '-' "back" in file, seeking back -1 so next call of fgetc() will iterate to it
                    //maybe make this -2 idk yet    

                    //outPrint(buffer, out, MINUSOP);  //places '-' in output file 
                return MINUSOP;
            }
        }
        else //character did not identify an ID, reserved word, Comment, intliteral, or minusop 
        {   //place this char in the buffer and list file 
            int i;
            switch(c)
            {
                default:        //making it default to error p much 
                    /*i = 1;
                    while (c != ' ' && c != '\n' && c != '\t' && c != EOF)
                    {
                        
                        buffer[i] = c;
                        fputc(c, list);
                        i++;
                    }*/
                    buffer[0] = c;
                    fputc(c, list);
;                   return ERROR;

                case '(':
                    fputc(c, list);
                    buffer[0] = c;
                    return LPAREN;

                case ')':
                    fputc(c, list);
                    buffer[0] = c;
                    return RPAREN;

                case ';':
                    fputc(c, list);
                    buffer[0] = c;
                    return SEMICOLON;

                case ',':
                    fputc(c, list);
                    buffer[0] = c;
                    return COMMA;

                case '+':
                    fputc(c, list);
                    buffer[0] = c;
                    return PLUSOP;

                case '*':
                    fputc(c, list);
                    buffer[0] = c;
                    return MULTOP;

                case '/':
                    fputc(c, list);
                    buffer[0] = c;
                    return DIVOP;

                case '!':
                    fputc(c, list);
                    buffer[0] = c;
                    return NOTOP;

                case '=':
                    fputc(c, list);
                    buffer[0] = c;
                    return EQUALOP;

                case 'eof':
                    fputc(c, list);
                    buffer[0] = c;
                    return SCANEOF;

                
                //2 character tests (":="     ">"   ">="      "<"   "<="      "<>")
                case ':':
                    //puts ':' in c and in token buffer
                        fputc(c, list);
                        buffer[0] = c;
                    
                    c = fgetc(in);  //moves and reads next char 
                    
                    if (c == '=')   //is next character '='
                    {   //if it is: 
                        fputc(c, list); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return ASSIGNOP;
                    }
                    else
                    {   //if it isn't 
                        fseek(in, -1, SEEK_CUR);    //set view back 
                        return ERROR;
                    }
                case '>':
                   
                    //is next char '='
                    //puts '>' in c and in token buffer
                    fputc(c, list);
                    buffer[0] = c;

                    c = fgetc(in);  //moves and reads next char 

                    if (c == ' ')   //is next char blank
                    {
                        return GREATEROP;
                    }
                    else if(c == '=')
                    {
                        fputc(c, list); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return GREATEREQUALOP;
                    }
                    else
                    {
                        fseek(in, -1, SEEK_CUR);
                        return ERROR;
                    }

                case '<':
                    //is next char blank
                    //is next char '='
                    //is next char '>'
                    fputc(c, list);
                    buffer[0] = c;

                    c = fgetc(in);  //moves and reads next char 

                    if (c == ' ')   //is next char blank
                    {
                        return LESSOP;
                    }
                    else if (c == '=')
                    {
                        fputc(c, list); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return LESSEQUALOP;
                    }
                    else if(c == '>')
                    {
                        fputc(c, list); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return NOTEQUALOP;
                    }
                    else
                    {
                        fseek(in, -1, SEEK_CUR);
                        return ERROR;
                    }
            }

        }
    }

   
}

void outPrint(char* buffer, FILE* out, int token)
{
    char* tokenType = (char*)malloc(BUFFER_SIZE * sizeof(char));
   //free(tokenType) 

    tokenIdentify(token, tokenType);

    fprintf(out, "Token number \t%d", token);
    fprintf(out, "\t\tToken type \t%s\t\t", tokenType );
    fprintf(out, "Actual token \t%s\n", buffer);    //adds the newline 

    free(tokenType);
}

void clearBuffer(char* buffer) 
{
    memset(buffer, '\0', BUFFER_SIZE);  //sets buffer to empty basically
}

void addChar(char* buffer, char c) 
{
    buffer[strlen(buffer)] = c;   //puts c in last spot in buffer
    buffer[strlen(buffer) + 1] = '\0';         //makes sure the spot after c is set to empty 
}

void tokenIdentify(int token, char* tokenType)
{
    switch (token)
    {
    case BEGIN:
        strcpy(tokenType, "BEGIN");
        break;
    case END:
        strcpy(tokenType, "END");
        break;
    case READ:
        strcpy(tokenType, "READ");
        break;
    case WRITE:
        strcpy(tokenType, "WRITE");
        break;
    case IF:
        strcpy(tokenType, "IF");
        break;
    case THEN:
        strcpy(tokenType, "THEN");
        break;
    case ELSE:
        strcpy(tokenType, "ELSE");
        break;
    case ENDIF:
        strcpy(tokenType, "ENDIF");
        break;
    case WHILE:
        strcpy(tokenType, "WHILE");
        break;
    case ENDWHILE:
        strcpy(tokenType, "ENDWHILE");
        break;
    case ID:
        strcpy(tokenType, "ID");
        break;
    case INTLITERAL:
        strcpy(tokenType, "INTLITERAL");
        break;
    case FALSEOP:
        strcpy(tokenType, "FALSEOP");
        break;
    case TRUEOP:
        strcpy(tokenType, "TRUEOP");
        break;
    case NULLOP:
        strcpy(tokenType, "NULLOP");
        break;
    case LPAREN:
        strcpy(tokenType, "LPAREN");
        break;
    case RPAREN:
        strcpy(tokenType, "RPAREN");
        break;
    case SEMICOLON:
        strcpy(tokenType, "SEMICOLON");
        break;
    case COMMA:
        strcpy(tokenType, "COMMA");
        break;
    case ASSIGNOP:
        strcpy(tokenType, "ASSIGNOP");
        break;
    case PLUSOP:
        strcpy(tokenType, "PLUSOP");
        break;
    case MINUSOP:
        strcpy(tokenType, "MINUSOP");
        break;
    case MULTOP:
        strcpy(tokenType, "MULTOP");
        break;
    case DIVOP:
        strcpy(tokenType, "DIVOP");
        break;
    case NOTOP:
        strcpy(tokenType, "NOTOP");
        break;
    case LESSOP:
        strcpy(tokenType, "LESSOP");
        break;
    case LESSEQUALOP:
        strcpy(tokenType, "LESSEQUALOP");
        break;
    case GREATEROP:
        strcpy(tokenType, "GREATEROP");
        break;
    case GREATEREQUALOP:
        strcpy(tokenType, "GREATEREQUALOP");
        break;
    case EQUALOP:
        strcpy(tokenType, "EQUALOP");
        break;
    case NOTEQUALOP:
        strcpy(tokenType, "NOTEQUALOP");
        break;
    case SCANEOF:
        strcpy(tokenType, "SCANEOF");
        break;
    case ERROR:
        strcpy(tokenType, "ERROR");
        break;
    case -1:
        strcpy(tokenType, "__No such token__");
        break;
    }
}

int reservedTest(char* buffer)
{
    while (*buffer) 
    {
        *buffer = toupper(*buffer);
        buffer++;
    }
        
    if (strcmp(buffer, "BEGIN") == 0)
    {
    return BEGIN;
    }
    else if (strcmp(buffer, "END") == 0)
    {
    return END;
    }
    else if (strcmp(buffer, "READ") == 0)
    {
    return READ;
    }
    else if (strcmp(buffer, "WRITE") == 0)
    {
    return WRITE;
    }
    else if (strcmp(buffer, "IF") == 0)
    {
    return IF;
    }
    else if (strcmp(buffer, "THEN") == 0)
    {
    return THEN;
    }
    else if (strcmp(buffer, "ELSE") == 0)
    {
    return ELSE;
    }
    else if (strcmp(buffer, "ENDIF") == 0)
    {
    return ENDIF;
    }
    else if (strcmp(buffer, "WHILE") == 0)
    {
    return WHILE;
    }
    else if (strcmp(buffer, "ENDWHILE") == 0)
    {
    return ENDWHILE;
    }
    else if (strcmp(buffer, "FALSEOP") == 0)
    {
    return FALSEOP;
    }
    else if (strcmp(buffer, "TRUEOP") == 0)
    {
    return TRUEOP;
    }
    else if (strcmp(buffer, "NULLOP") == 0)
    {
    return NULLOP;
    }
    else 
    {
    return -1; // Handles unknown token, returns -1 on error
    }
}

///haven't done ant of the ones below this, just declared them 


int ErrorHandler(char* buffer, char* errList, int errFlag)
{
    if (errFlag == 33)
    {
        int i = 0;
        while (buffer[i] != '\0') 
        {
            i++;
        }

        i--;

        // Check if the last character is not a space, newline, or tab
        if (i >= 0 && (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t'))
        {
            strcat(errList, buffer);
            return 1;
        }
    }
    return 0;
}

