#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHARACTERS 1000

int passwordCheck(char password[MAX_CHARACTERS])
{
	//used to tell whether or not the password passed the check, total >=3 passed.
	int total = 0;
	// holds a 1 if the type of character is found, holds a 0 if not, is added to the total after the check is complete
	int capital = 0;
	int lower = 0;
	int specialChar = 0;
	int number = 0;
	
	int result;	//used to hold the result of each function check
	
	//length check
    if(strlen(password)<4 || strlen(password)>25)
    {
        printf("Error! Min:8 Characters and Max:25 characters!\n");   
        for(int i=0;i<strlen(password);i++)
        {
           password[i] = 0;
        }  
        return 0;
    }
	
	for(int i=0; i<= MAX_CHARACTERS; i++)
	{
		//assigns the result of isupper to the result variable and check if its greater than 0
		result = isupper(password[i]);
		//if the result is greater than 0 then the character is a capital letter
		if(result > 0)
		{
			//if the capital value is 0 it will add 1 to it to acknowledge we have a capital in the password
			if(capital == 0)
			{
				capital=1;
			}
		}
		//assigns the result of islower to the result variable and checks if it is greater than 0
		result = islower(password[i]);
		//if the result is greater than 0 then the character is a lower case letter
		if(result > 0)
		{
			//if the lower value is 0 it will add 1 to it to acknowledge we have a lower case letter in the password
			if(lower == 0)
			{
				lower=1;
			}
		}
		//assigns the result of ispunct to the result variable and checks if its greater than 0
		result = ispunct(password[i]);
		//if the result is greater than 0 then the character is a special character
		if(result > 0)
		{
			//if the specialChar value is 0 it will add 1 to it to acknowledge we have a special character in the password
			if(specialChar == 0)
			{
				specialChar=1;
			}
		}
		//assings the result of isdigit to the result variable and checks if its greater than 0
		result = isdigit(password[i]);
		//if the result is greater than 0 then the character is a number
		if(result > 0)
		{
			//if the number value is 0 it will add 1 to it to acknowledge we have a numeber in the password
			if(number == 0)
			{
				number=1;
			}
		}
	}
	//adds all of the values to total if total >= 3 we have an password that meets the requirements.
	total = number + specialChar + lower + capital;
	if(total > 3)
	{
		printf("you have a good password \n");
		return 1;
	}
	else
	{
		printf("your password does not meet requirements \n");
		return 0;
	}
	
	//if it returns a 1 the password is good, if it returns a 0 then the password is bad
}

    	
int main()
{
    char pass[MAX_CHARACTERS] = {"pAsswordA!"};
    
    
    int passwordResult = passwordCheck(pass);
    
    printf("%d", passwordResult);
    
    return 0;
    
}



