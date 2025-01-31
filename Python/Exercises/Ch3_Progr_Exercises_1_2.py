
#Write a program that uses nested loops to collect data and calculate the average rainfall over
#a period of years. The program should first ask for the number of years. The outer loop will
#iterate once for each year. The inner loop will iterate twelve times, once for each month.
#Each iteration of the inner loop will ask the user for the inches of rainfall for that month.
#After all iterations, the program should display the number of months, the total inches of
#rainfall, and the average rainfall per month for the entire period.


years = int(input("Enter a number of years: "))
months = 12
totMonths = years * 12
totalRain = 0.0
avgRain = 0.0

while (years > 0):
    years-=1
    months = 12
    while (months > 0):
        totalRain += float(input("Please enter the ammount of rain in this month:"))
        months -= 1

avgRain = totalRain/totMonths

print(f"Over the course of {totMonths} months there was {totalRain} inches of rain, or an everage of {avgRain} inches ")


