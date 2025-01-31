
#chapter 5
#    exercise 
#        #12
#        #20
#12. Maximum of Two Values
#Write a function named max that accepts two integer values as arguments and returns the
#value that is the greater of the two. For example, if 7 and 12 are passed as arguments to
#the function, the function should return 12. Use the function in a program that prompts the
#user to enter two integer values. The program should display the value that is the greater
#of the two

#12
def max(i: int, j: int):
    if(i > j):
        return i
    else:
        return j

i = int(input("Enter a number\n"))
j = int(input("Enter a number\n"))

print(max(i,j))


#20
#20. Random Number Guessing Game
#Write a program that generates a random number in the range of 1 through 100, and asks
#the user to guess what the number is. If the user’s guess is higher than the random number,
#the program should display “Too high, try again.” If the user’s guess is lower than the
#random number, the program should display “Too low, try again.” If the user guesses the
#number, the application should congratulate the user and generate a new random number
#so the game can start over.
#Optional Enhancement: Enhance the game so it keeps count of the number of guesses that
#the user makes. When the user correctly guesses the random number, the program should
#display the number of guesses
import random

guess = int(input("Enter your guess"))
num = random.randint(1,100)
while(guess != num):
    guess = int(input("Enter your guess"))

    if(guess>num):
        print("Too high, try again")
    elif(guess<num):
        print("too low, try again")
    elif(guess == num):
        print("you guessed it, congratulations")