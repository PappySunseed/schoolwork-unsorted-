#Exercise 1 and 6, page 427
#1. Total Sales
#Design a program that asks the user to enter a store’s sales for each day of the week. The
#amounts should be stored in a list. Use a loop to calculate the total sales for the week and
#display the result.
sales = [0]
sales = [sales[0]] * 7
total = 0

def get_day_name(i):
    days = {
        0: "Monday",
        1: "Tuesday",
        2: "Wednesday",
        3: "Thursday",
        4: "Friday",
        5: "Saturday",
        6: "Sunday"
    }
    return days.get(i, "Invalid day")

for i in range(len(sales)):
    day_name = get_day_name(i)
    sales[i] = int(input(f"Sales on {day_name}: "))
    total += sales[i]


avg = total /7
print("Average:", avg)




#6. Larger Than n
#In a program, write a function that accepts two arguments: a list, and a number n. Assume
#that the list contains numbers. The function should display all of the numbers in the list
#that are greater than the number n.

def who_greater(list, num):


    j = 0
    for j in range(len(list)):
        if(list[j] > num):
            print(list[j])
    return
            

who_greater(sales, 3)