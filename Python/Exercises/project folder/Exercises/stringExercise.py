#. Date Printer
#Write a program that reads a string from the user containing a date in the form mm/dd/yyyy.
#It should print the date in the format March 12, 2018
try: 
    date_input = input("Enter the date in the format mm/dd/yyyy: ")
    
    month, day, year = map(int, date_input.split('/'))

    # Mapping month numbers to month names
    months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    month_name = months[month - 1]  

    # Printing the date in the desired format
    print(f"The formatted date is: {month_name} {day}, {year}")
except ValueError:
    print("Invalid date format. Please enter the date in the format mm/dd/yyyy.")
    