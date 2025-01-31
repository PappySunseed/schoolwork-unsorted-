/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/
#include "Scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"

linenumber = 1;
//long original_position[BUFFER_SIZE];
long original_position;
char c;
int first = 1;
int tokenScanner(char* buffer, char* errList, FILE* in, FILE* out, FILE* list) //returns the enumerated next token 
{
    if(first == 1)
    {
        fprintf(list, "%d.  ", linenumber);
        first = 0;
        linenumber++;
    }

    int ascii;
    printf("\nScanning in progress...");
    clearBuffer(buffer);   //clear input buffer 


    c = fgetc(in);          //read from file pointer 
  
    while (c != EOF)  //read from input file 
    {
       //consume whitespace
        while (c == ' ' || c == '\t')
        {
            c = fgetc(in);
        }
        //printf("\nCharacter right after white space %c", c);
        ascii = (int)c; //converts c to ascii value
        
        //need to check if first char is alphabet first, to see if variable name basically
        if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))// || (ascii > 47 && ascii < 58))     //if the ASCII value of c is within the alphabet values 
        {
            int i = 0;  //local counter for buffer[]
        
            while ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123) || (ascii > 47 && ascii < 58)) //copies whole string of letters/numbers after first alpha char
            {
               updateList(c, list, in); //place char in list file
                buffer[i] = c;  //places char in token buffer
                //buffer[i+1] = '\0';
                c = fgetc(in);  //advance next char from 'in'
                ascii = (int)c; //get ascii value for next char
                i++;            //advanced for token buffer 

            }
            ungetc(c, in);
            //printf("\nHanging character after while loop: %c \n", c);
            //printf("Buffer: %s.\n", buffer);
            //***at this point the entire alphanumeric string has been read and saved***

            int returnint = reservedTest(buffer);
            if(returnint > 0)
            {
                    //outPrint(buffer, out, isReserved(buffer));
                //printf("Buffer: %s.   Return int: '%d'\n", buffer,returnint);
                return returnAndPrint(returnint, buffer);
                
            }
            else
            {
                    //outPrint(buffer, out, ID);
                return returnAndPrint(ID, buffer);
            }

        }
        else if ((ascii > 47 && ascii < 58))    //if char after '-' is a digit 
        {
           
            int i = 0; //for buffer
            while ((ascii > 47 && ascii < 58))   //reads all consecutive digits 
            {
               updateList(c, list, in); //place char in list file
                buffer[i] = c;  //places digit in token buffer

                c = fgetc(in);  //advance next char from 'in'
                ascii = (int)c; //get ascii value for next char
                i++;            //advanced for token buffer
            }
            ungetc(c, in);

            //token buffer now contains an INTLITERAL  
                //outPrint(buffer, out, ID);  //places this int literal into output file as token type ID
            return returnAndPrint(INTLITERAL, buffer);
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
                   updateList(c, list, in);
                    c = fgetc(in);
                }
                return returnAndPrint(tokenScanner(buffer, errList, in, out, list), buffer);
            }
            else if ((ascii > 47 && ascii < 58))    //if char after '-' is a digit 
            {
                int i = 0; //for buffer[]                        
                buffer[i] = hold;   //places '-' in buffer
                i++;
                fputc(hold, list); //place first '-' in list file
                while ((ascii > 47 && ascii < 58))   //reads all consecutive digits 
                {
                   updateList(c, list, in); //place char in list file
                    buffer[i] = c;  //places digit in token buffer

                    c = fgetc(in);  //advance next char from 'in'
                    ascii = (int)c; //get ascii value for next char
                    i++;            //advanced for token buffer
                }
                ungetc(c, in);

                //token buffer now contains an INTLITERAL  
                    //outPrint(buffer, out, ID);  //places this int literal into output file as token type ID
                return returnAndPrint(INTLITERAL, buffer);
            }
            else //when the char after '-' isn't a digit or a second '-' it will now be treated as a minus operator 
            {
                buffer[0] = hold;   //places what should be '-' in buffer
                ungetc(c, in);    //"puts" the char after '-' "back" in file, seeking back -1 so next call of fgetc() will iterate to it
                    //maybe make this -2 idk yet    

                    //outPrint(buffer, out, MINUSOP);  //places '-' in output file 
                return returnAndPrint(MINUSOP, buffer);
            }
        }
        else //character did not identify an ID, reserved word, Comment, intliteral, or minusop 
        {   //place this char in the buffer and list file 
            int i;
            //printf("\ngot to the switch, here's last character read: '%c'\n", c);
            if (feof(in))
            {
                return returnAndPrint(SCANEOF, buffer);
            }
            switch(c)
            {
                
                default:        //making it default to error p much 
                  
                    buffer[0] = c;
                    updateList(c, list, in);
;                   return returnAndPrint(ERROR, buffer);
                case '\n':
                    if (ftell(in) != original_position) {
                        // Append buffer to statementOut only if the position has changed
                        fputc(c, list);
                        fprintf(list, "%s", errList);
                        strcpy(errList, "\0");
                        fprintf(list, "%d.  ", linenumber);
                    }
                    original_position = ftell(in);
                    updateList(c, list, in);
                    linenumber++;
                    
                   
                    
                   // fprintf(list, "%d.  ", linenumber);
                    return returnAndPrint(tokenScanner(buffer, errList, in, out, list), buffer);
                case ' ':
                    updateList(c, list, in);
                    return returnAndPrint(tokenScanner(buffer, errList, in, out, list), buffer);
                case '\t':
                   updateList(c, list, in);
                    return returnAndPrint(tokenScanner(buffer, errList, in, out, list), buffer);
                case '\0':
                   updateList(c, list, in);
                    return returnAndPrint(tokenScanner(buffer, errList, in, out, list), buffer);

                case '(':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(LPAREN, buffer);

                case ')':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(RPAREN, buffer);

                case ';':
                    //linenumber--;
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(SEMICOLON, buffer);

                case ',':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(COMMA, buffer);

                case '+':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(PLUSOP, buffer);

                case '*':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(MULTOP, buffer);

                case '/':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(DIVOP, buffer);

                case '!':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(NOTOP, buffer);

                case '=':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(EQUALOP, buffer);

                case 'EOF':
                   updateList(c, list, in);
                    buffer[0] = c;
                    return returnAndPrint(SCANEOF, buffer);

                
                //2 character tests (":="     ">"   ">="      "<"   "<="      "<>")
                case ':':


                    //puts ':' in c and in token buffer
                   updateList(c, list, in);
                    buffer[0] = c;
                    
                    c = fgetc(in);  //moves and reads next char 
                    
                    if (c == '=')   //is next character '='
                    {   //if it is: 
                       updateList(c, list, in); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return returnAndPrint(ASSIGNOP, buffer);
                    }
                    else
                    {   //if it isn't 
                        ungetc(c, in);    //set view back 
                        return returnAndPrint(ERROR, buffer);
                    }
                case '>':
                   
                    //is next char '='
                    //puts '>' in c and in token buffer
                   updateList(c, list, in);
                    buffer[0] = c;

                    c = fgetc(in);  //moves and reads next char 

                  if(c == '=')
                    {
                       updateList(c, list, in); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return returnAndPrint(GREATEREQUALOP, buffer);
                    }
                    else
                    {
                      ungetc(c, in);
                        return returnAndPrint(GREATEROP, buffer);
                    }

                case '<':
                    //is next char blank
                    //is next char '='
                    //is next char '>'
                   updateList(c, list, in);
                    buffer[0] = c;

                    c = fgetc(in);  //moves and reads next char 

                    if (c == '=')
                    {
                       updateList(c, list, in); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return returnAndPrint(LESSEQUALOP, buffer);
                    }
                    else if(c == '>')
                    {
                       updateList(c, list, in); //put it in list file 
                        buffer[1] = c;  //put it in buffer 
                        return returnAndPrint(NOTEQUALOP, buffer);
                    }
                    else
                    {
                        ungetc(c, in);
                        return returnAndPrint(LESSOP, buffer);
                    }
            }
        }
       
    }
    return returnAndPrint(100, buffer);
}

int updateList(char c, FILE* list, FILE* in)
{
    int on = 0;
    int visited = 0;
    int newvis = 0;

    long currentPosition = ftell(in);

    if (on == 1)
    {
        //for (int i = 0; i < BUFFER_SIZE; ++i)
        //{
        //    if (original_position[i] == currentPosition)
        //    {
        //        visited = 1;  // Value found
        //        newvis = i + 1;
        //    }
        //}

            // Ensure that the current position in the list file is different from the original position
            if (visited == 0)
            {
               // fputc(c, list);
                // If the linenumber is 1 or a newline character is encountered, print the linenumber prefix
                if (c == '\n')
                {
                    fprintf(list, "%d.  ", linenumber);
                }
            }
            // Update the original position to the current position in the list file
           // original_position[newvis] = ftell(in);
    }
    else
    {
       // fputc(c, list);
    }
    
    
        return 0;
   }

int returnAndPrint(int returnValue, char* buffer)
{
    printf("\nScanning returned: '%d'   Buffer: '%s'\n", returnValue, buffer);
    return returnValue;  // Return the value
}
void outPrint(char* buffer, FILE* out, int token)
{
    char* tokenType = (char*)malloc(BUFFER_SIZE * sizeof(char));
   //free(tokenType) 

    tokenIdentify(token, tokenType);
    printf("\nToken before printing %s\n", tokenType);

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
    char* OGbuffer = buffer;
    //printf("\nBuffer in the reserved test function before to upper: %s.\n", buffer);
    while (*OGbuffer) {
        *OGbuffer = toupper((unsigned char)*OGbuffer);
        OGbuffer++;
    }

    //printf("Buffer in the reserved test function: '%s'\n", buffer);
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

int ErrorHandler(char* buffer, char* errList, int errFlag)
{
    if (errFlag == 33)
    {   
        sprintf(errList, "Error found in line %d: ", linenumber);

        strcat(errList, buffer);
        strcat(errList, "\n");
        
        return 1;
    }
    return 0;
}

int getLineNum()
{
    return linenumber;
}