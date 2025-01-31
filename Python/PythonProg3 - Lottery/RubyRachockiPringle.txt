
#
# Program"s name: Python Project 3: lottery number generator
# Programmer's names: Caleb Rachocki, Caleb Ruby, Austin Pringle
# Date: 2/27/2024
# Program's Purpose: To randomly generate numbers into a list and have the user place bets on if a number is in said list
#

import random

def generateList(List):
     userInput = input("Would you like to view the list for test purposes? (Y/N): ")
     #list initialization section
     ##print("List printed for test purposes:")
     #this for loop goes through 5 times for each position in the list
     for i in range(5):
          #pickOneNumber generates a random number from the range 1-9
          Number = random.randrange(0,10)
          #this while loop prevents anything already in the list from being put into the list
          while Number in List:
               Number = random.randrange(0,10)
          else:
               List[i] = Number
     if userInput.upper() == "Y":
          print(List)


def pickOne(pickOneList):
    #this userInput asks the user to choose 1 number for the pick one game
     userInput = int(input("Please choose a number (0-9): "))

     if userInput >= 0 and userInput < 10:
         if userInput in pickOneList:
          #if the user picks a number in the list the function returns a 1
          return 1
         else:
          #if the user picks a number not in the list the function returns a 0
          return 0
     else:
          print("Invalid selection")

def pickTwo(pickList):
    #this userInput asks the user to choose 1 number for the pick one game
     inputOne = int(input("Please choose the first number (0-9): "))
     inputTwo = int(input("Please choose the second number (0-9): "))

     if inputOne >= 0 and inputTwo < 10 and inputTwo >= 0 and inputOne < 10:
         if inputOne in pickList and inputTwo in pickList:
             return 1
         else:
             return 0
          
     else:
          print("Invalid selection")

def jumbo():
     jumList = [-1,-1,-1,-1,-1, -1, -1] #creates the list with 7 values of 0
     correct = 0

     #list initialization section
    ## print("List printed for test purposes:")
     #this for loop goes through 7 times for each position in the list
     for i in range(7):
          #pickOneNumber generates a random number from the range 1-9
          Num = random.randrange(0,10)
          #this while loop prevents anything already in the list from being put into the list
          while Num in jumList:
               Num = random.randrange(0,10)
          else:
               jumList[i] = Num
               
     userInput = input("Would you like to view the list for test purposes? (Y/N): ")
     if userInput.upper() == "Y":
          print(jumList)

     for i in range(7):
          inp = int(input(f"Guess number {i+1}: "))    #gets input
          if inp in jumList:    #if that input is in the list 
              correct = correct + 1 #increment total correct guesses
              jumList.remove(inp)   #remove that number from the list so only one guess of each number will count; list can't have repeats anyways
     if correct == 6:
        return 1
     elif correct == 7:
        return 2
     else:
        return 0


def main():
     chips = 100 
     bet = 0
     gamestate = 1
     List = [-1,-1,-1,-1,-1] #creates the list with 5 values of 0
     
     print("Game will continue until user is out of chips or presses 4 to quit\n")
     
     while gamestate == 1:
          bet = 0
          generateList(List)
          print("Game choices: Pick One (1), Pick Two (2), and the Jumbo (3)")

          userInput = int(input("Enter 1, 2, or 3 to select game or 4 to quit: "))        #get user game choice
          while (bet < 1 or bet > 10) and userInput != 4:
               bet = int(input("How many chips would you like to bet? (1-10): ")) #get user bet 
               if(bet < 1 or bet > 10):
                    print("please enter an amount within the expected parameters")
                    
          chips = chips - bet

          if userInput >= 1 and userInput <= 3:  #if user makes valid game choice 
               if userInput == 1:    #if user chooses pick one 
                    print("\nYou have selected the Pick One game")
                    print("in this game you will select 1 number from 0-9")

                    if pickOne(List) == 1:   #win case
                         print(f"\nyou won {bet} chips yipee")
                         chips = chips + bet + bet 
                         print(f"you now have {chips} chips")
                    else:
                        print("\nYou lost, womp womp")
                        print(f"you now have {chips} chips")
               elif userInput == 2:  #user selected pick two game
                    print("\nYou have selected the Pick Two game")
                    print("in this game you will select 2 numbers from 0-9")

                    if pickTwo(List) == 1:   #win case
                         print(f"\nyou won {bet*2} chips yipee")
                         chips = chips + bet*2 + bet
                         print(f"you now have {chips} chips")
                    else:
                        print("\nYou lost, womp womp")
                        print(f"you now have {chips} chips")
               elif userInput == 3:  #user selects jumbo game
                    print("\nYou have selected the Jumbo game")
                    print("in this game you will select 7 numbers from 0-9")
                    print("If you correctly guess 6 numbers you win. If you guess all 7 you get the jackpot.")

                    i = jumbo()
                    if i == 1:   #small win case
                         print(f"\nyou won with 6 correct guesses, you got {bet*5+27} chips yipee")
                         chips = chips + bet + bet*5 + 27
                         print(f"you now have {chips} chips")
                    elif i == 2:
                         print(f"\nyYou got all 7 correct guesses, you win {bet*53} chips yipee")
                         chips = chips + bet + bet*53
                         print(f"you now have {chips} chips")
                    else:
                         print("\nYou lost, womp womp")
                         print(f"you now have {chips} chips")
               else:
                    print("error invalid input try again")
          if chips <= 0 or userInput == 4:
               print("Game ending, goodbye...")
               gamestate = 0


main()