/*
Group 3 - Language Translation CMSC 4180 001

Program 3 Parser

Caleb Ruby - rub4133@pennwest.edu
Tanner Kirsch - kir0510@pennwest.edu
Adeer Turgeman - tur28711@pennwest.edu

*/

#ifndef FILE_UTIL
#define FILE_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* bak, * temp, * temp2, *in, *out, *list;
char outname[50];
char* outAppend[50];

//___________File Information functions _____________
int hasExt(char* fileName);
/// <summary> 
/// Checks a string for an extension by decrementing from the last char of the string until it finds a period 
/// 
/// <params>
///  name="fileName" (filename you wish to be checked. Needs to be a valid char[])
/// 
/// <returns>
/// returns -1 if no extension found
/// returns 1 if extension found 
/// 

int validIn(char* fileName);
/// <summary> 
/// Checks an input file name for validity (that file existing)
/// 
/// <params>
///  name="fileName" (filename you wish to be checked. Needs to be a valid char[])
/// 
/// <returns>
/// returns -1 if invalid
/// returns 1 if valid 

int validOut(char* fileName);
/// <summary> 
/// Checks an output file name for validity (that file not-existing)
/// 
/// <params>
///  name="fileName" (filename you wish to be checked. Needs to be a valid char[])
/// 
/// <returns>
/// returns -1 if invalid
/// returns 1 if valid 

int isOpen(FILE* f);
/// <summary> 
/// Checks if a file opened successfully
/// 
/// <params>
///  name="f" (FILE* pointer of the file to be checked)
/// 
/// <returns>
/// returns -1 if file didn't open
/// returns 1 if file opened 

void fileCopy(FILE* src, FILE* dest);
/// <summary> 
/// Reads and writes each char from src to dest
/// 
/// <params>
/// name="src" (FILE* pointer to the file to be read from)
/// name = "dest" (FILE* pointer to file to be written to)
/// 
/// <returns>
/// returns void

FILE* openFile(char* filename, char* fileMode);
/// <summary> 
/// opens a file and calls "isOpen()" to validate the file opening
/// 
/// <params>
///  name="fileName" (filename you wish to be checked. Needs to be a valid char[])
/// name = "fileMode" (single char which determines open mode of the file)
/// 
/// <returns>
/// returns a FILE* pointer to the open file 





void createFilesInDirectory(const char* outFile, const char* listFile);
#endif
