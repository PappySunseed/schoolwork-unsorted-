#include "Scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tokenScanner(char* buffer, FILE* in, FILE* out, FILE* list) //returns the enumerated next token 
{
	int linenumber = 0;
	int startofline = 1;

    char c;

    while ((c = fgetc(in)) != EOF)
    {
        if (startofline)
            fprintf(list, "%d.  ", ++linenumber);  /* put line number in output file */

        fputc(c, list);
        startofline = c == '\n';
    }
}