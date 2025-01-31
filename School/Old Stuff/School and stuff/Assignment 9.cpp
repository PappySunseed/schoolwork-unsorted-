#include <stdio.h>
int main(){

	
//this allows user to input the grades

			//for some reason the program breaks when i have scanf in the loop

float grade[9];

printf("enter the grades \n");

int x=0;

Loop:
	
	scanf("%f\n",grade[x]);
	if (grade[x]>100 or grade[x]<0)
		grade[x]=0;
			x--;
				goto LoopEnd;
if (x<9)
	goto Loop;	

LoopEnd:
	
printf("%d\n",x);



}
