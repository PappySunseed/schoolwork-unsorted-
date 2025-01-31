#include <iostream>
#include <string>
#include <fstream>
#include "employee.h"

using namespace std;

int main(void)
{	
	ifstream inp;
	
	Employee employee1;	

	//The following variables temporarily hold data from input file.
	string input;		//Tracks first and last name input	
	int tempWorked;		//Temporarily holds hours worked
	double tempRate;	//Temporarily holds hourly rate
	int infoCount = 1;	//Tracks what data form (names, pay, rates) program is on.
	
	//Following lines open the input file.
	inp.open("input.txt");
	
		if(!inp)
	{
		cout << "Input file not found..." << endl;
		exit(0);
	}
	
	
	string err ("**error**");	//makes error string for simplicity's sake.. Called on to display error message
	int errcount;
	   
	   
	//Following lines are meant to set temp variables equal to respective data in the input file
	while(getline(inp, input))	//While loop utilizes a getline to read until end of file.
	{
		if(infoCount == 1)
		{
			
			std::size_t found = input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");	//searches line for first non-alphabet character		repeated for last name 
			
			if (found!=std::string::npos)																			//if non if it finds one, error is displayed 			repeated for last name 
			{
				employee1.setFirstName(err);
			}
			else																									//if non-alphabet character is not found, passes the line to setter function			repeated for last name 
			{
				employee1.setFirstName(input);
			}
			
			
			infoCount++;
		}
		else if(infoCount == 2)
		{
			
			std::size_t found = input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			
			if (found!=std::string::npos)
			{
				employee1.setLastName(err);
			}
			else
			{
				employee1.setLastName(input);
			}
			
			infoCount++;
		}
		else if(infoCount == 3)
		{
			std::size_t found = input.find_first_not_of("0123456789");
			if(found!=std::string::npos)										//sets HoursWorked to 0 if bad data found
			{
				employee1.setHoursWorked(-1);
			}
			else																//sets HoursWorked to integer data gathered from getline when good data 
			{
				tempWorked = stoi(input);
				employee1.setHoursWorked(tempWorked);
			}
			
			
			infoCount++;
		}
		else if(infoCount == 4)
		{
			size_t found = input.find_first_not_of("0123456789.");
			if(found!=std::string::npos)										//sets HourlyRate to 0 if bad data found
			{
				employee1.setHourlyRate(-1);
			}
			else																//sets HoursWorked to integer data gathered from getline when good data 
			
			{
				tempRate = stof(input);
				employee1.setHourlyRate(tempRate);
			}
						
			infoCount = 1;
			
			
			employee1.setGrossPay();	//Calls the setGrossPay function to calculate the grossPay of an employee
			employee1.display();		//Calls the display function to output all required employee information
		}
	}
	return 0;
}
