#
# Program"s name: Python Project 3: lottery number generator
# Programmer's names: Caleb Rachocki, Caleb Ruby, Austin Pringle
# Date: 2/27/2024
# Program's Purpose: To randomly generate numbers into a list and have the user place bets on if a number is in said list
#

import random

def pickOne():
     #intializes the list with 5 values of 0
     pickOneList = [0, 0, 0, 0, 0]
     #this for loop goes through 5 times for each position in the list
     for i in range(5):
          #pickOneNumber generates a random number from the range 1-9
          pickOneNumber = random.randrange(1,9)
          #this while loop prevents anything already in the list from being put into the list
          while pickOneNumber in pickOneList:
               pickOneNumber = random.randrange(1,9)
          else:
               pickOneList[i] = pickOneNumber
               print(pickOneList[i])
     #this userInput asks the user to choose 1 number for the pick one game
     userInput = int(input("Please choose 1 number from the range 1-9"))
     if userInput in pickOneList:
          #if the user picks a number in the list the function returns a 1
          return 1
     else:
          #if the user picks a number not in the list the function returns a 0
          return 0


def main():
     userChips = 100

     print("Please pick a number to select a game to play")
     print("Pick One (1), Pick Two (2), and the Jumbo (3)")

     #the initial user Input
     userInput = int(input("Enter a number between 1-3 to select your game: "))

      #this while loop is for proper data entry, it prevents the user from entering in any number outside of the proper range 1-9
     while userInput >= 1 and userInput <= 3:
          if userInput == 1:
               print("You have selected the Pick One game")
               print("in this game you will select 1 number from 1-9")
               userInput = int(input("How much would you like to bet (1-9): "))
               pickOne()
          elif userInput == 2:
               print("pick 2")
          elif userInput == 3:
               print("jumbo")
          else:
               print("error invalid input try again")

main()