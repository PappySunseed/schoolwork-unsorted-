// CLASS PROVIDED:  Employee
//
// CONSTRUCTOR for the Employee class:
//   Employee()
//     Description:		constructor will initialize Employee objects
//     Preconditions:	none
//     Postcondition:	Employee has been set to PLACEHOLDER, PLACEHOLDER, 0, 0
//
// MODIFICATION MEMBER FUNCTIONS for the Employee class
//   void setFirstName (const string entry)
//     Description:		set the first name of the employee
//     Precondition:	entry is string less than 15 characters
//     Postcondition:	entry is set to first
//
//   void setLastName (const string entry)
//     Description:		set the last name of the employee
//     Precondition:	entry is string less than 15 charactersa
//     Postcondition:	entry is set to last
//
//   void setHoursWorked  (const int hours)
//     Description:		set the number of hours worked for employee
//     Precondition:	hours is non-negative
//     Postcondition:	hours is set to worked
//
//   void setHourlyRate  (const double hourlyRate)
//     Description:		set the hourly wage of the employee
//     Precondition:	hourlyRate is >= 0
//     Postcondition:	hourlyRate is set to rate
//
//	  void setGrossPay	 (void)
//		Description:	set the gross pay of the employee
//		Precondition:	variables rate and worked are accepyable data
//		Postcondition:	grossPay is caluculated and set to grossPay
//
// CONSTANT MEMBER FUNCTIONS for the Fraction class
//
//   string  getFirstName(void) const
//     Description:		obtain first name of the employee
//     Preconditions:	none
//     Postcondition:	first name of employee is returned
//
//   string  getLastName  (void) const
//     Description:		obtain last name of the employee
//     Preconditions:	none
//     Postcondition:	last name of employee is returned
//
//   int  getHoursWorked  (void) const
//     Description:		obtain hours worked by employee
//     Preconditions:	none
//     Postcondition:	hours worked by employee is returned
//
//   double getHourlyRate (void) const
//     Description:		obtain hourly rate of employee
//     Preconditions:	none
//     Postcondition:	hourly rate of employee is returned
//
//   double getGrossPay 	  (void) const
//     Description:		obtain gross pay of the employee
//     Preconditions:	none
//     Postcondition:	gross pay of th employee is returned
//
//   void display (void) const
//     Description:		display employee information to screen
//     Preconditions:	All private data is entered
//     Postcondition:	employee information is displayed on the screen
//
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

using namespace std;

class Employee
{
  //Public data, can be used/altered with setters and getters
  public:
    // CONSTRUCTOR
    Employee();

    // MODIFICATION MEMBER FUNCTIONS (setters)
    void setFirstName		(const string);
    void setLastName		(const string);
    void setHoursWorked		(const int);
    void setHourlyRate		(const double);
    void setGrossPay		(void);

    // CONSTANT MEMBER FUNCTIONS (getters)
    string	 getFirstName		(void) const;
    string	 getLastName		(void) const;
    int		 getHoursWorked		(void) const;
    double	 getHourlyRate		(void) const;
    double	 getGrossPay		(void) const;
    void 	 display 			(void) const;

  //Hidden data, can only be changed w/ setters
  private:
	string	first;
    string	last;
    int 	worked;
    double 	rate;
    double  grossPay;
};

#endif
