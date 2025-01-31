#ifndef FILE_UTIL
#define FILE_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//___________File Information functions _____________
int hasExt(char* fileName);
bool validIn(char* fileName);
bool validOut(char* fileName);



//___________File Creation functions _____________
void createBackup(char* fileName);
/*
*	Description:	-creates a backup file, format "fileName.back"
*					
* 
*	required Parameters:	valid filename you wish to create backup from 
* 
*/

void creatList(char* fileName);
/*
*	Description:	-creates a list file, format "fileName.lis"
*
*
*	required Parameters:	valid filename you wish to create list from
*
*/



#endif
