#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "employee.h"

using namespace std;

// CONSTRUCTOR
//Both first and last initialize with PLACEHOLDER, a 10 character string. 15 is the max.
//worked and grossPay initialize with values of 0.
//rate initializes with minimum value, 6.50
Employee::Employee()
{
	first = "ERROR";
	last = "ERROR";
	worked = 0;
	rate = 6.50;
	grossPay = 0;
}


// MODIFICATION MEMBER FUNCTIONS
void Employee::setFirstName (const string entry)
{
	if(entry.length() <= 15)
	{
		first = entry;
	}
}


void Employee::setLastName(const string entry)
{
	if(entry.length() <= 15)
	{
		last = entry;
	}
}


void Employee::setHoursWorked(const int hours)
{	
	if(hours >= 0 && hours <=50)
	{
		worked = hours;
	}
	else
	{
		worked = -1;
	}
}


void Employee::setHourlyRate(const double hourlyRate)
{
	if(hourlyRate >= 6.50 && hourlyRate <= 25.75)
	{
		rate = hourlyRate;
	}
	else
	{
		rate = -1;
	}
}


void Employee::setGrossPay(void)
{
	grossPay = worked * rate;
	
	if (rate == -1)		//changes grosspay to 0 if rate is invalid input
	{
		grossPay = -1;
	}		
}		

// CONSTANT MEMBER FUNCTIONS
string Employee::getFirstName(void) const
{
  return first;
}


string Employee::getLastName(void) const
{
  return last;
}


int Employee::getHoursWorked(void) const
{
  return worked;
}


double Employee::getHourlyRate(void) const
{
  return rate;
}


double Employee::getGrossPay(void) const
{
  return grossPay;
}


void Employee::display(void) const
{
	string grossPayError = to_string(grossPay);			//turns grossPay to a string so an error message can be put in its place
	int check = grossPay;									//Check variable to act similarly to a boolean in the following if statement

	if(check == -1)											//makes the string version of grossPay **error** if it was found to be bad data
	{
		grossPayError = ("**error**");						//Allows for the display of an error message in place of grossPay
		cout << last << " " << setw( 20 - last.length() ) << first << " ";
		cout << setw(31) << grossPayError << " " << endl;	
	}
	else
	{
		if (last.length() + first.length() == 30)	//Checks if total string length of first and last are greater than 30. Creates 1 whitespace.
		{
			cout << last << " " << setw( 20 - last.length() ) << first << " ";
			cout << setw(21) << grossPay << fixed << setprecision(2) << " " << endl;
		}
		else
		{
			cout << last << " " << setw( 20 - last.length() ) << first << " ";
			cout << setw(31) << grossPay << fixed << setprecision(2) << " " << endl;
		}
	}
	
	/*
	To be totally transparent, I was unsure of how to get our output to specifically display 2 decimals of a 
	double variable, but I did remember it was possible in C. Referring back to that book, I looked up the C++ 
	equivalent of precision and found a solution online through CodeGrepper. The same is true for our
	field width equivalent, setw() Links below. We just want to be honest.

	Precision:
	https://www.codegrepper.com/code-examples/cpp/print+float+to+2+decimal+places+c%2B%2B
	
	Field Width/setw()
	https://www.simplilearn.com/tutorials/cpp-tutorial/setw-cpp#:~:text=In%20simple%20terms%2C%20the%20setw,stream%20out%20exactly%20n%20times.

	*/

}

