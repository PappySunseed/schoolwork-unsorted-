#IMPORTS:

import random   #randomness library


#
#THE run() FUNCTION
#Params: None
#Returns: An int representing the number of yards gained on the run
#
#The run() function calculates the amount of yards gained from a run play.
#It prompts the player to choose between 2 types of run:
# * The high-risk, high-reward "RISKY" play
# * The low-risk, low-reward "CONSERVATIVE" play
#The player can also choose to go back to the main game menu.
#
def run():

    #The yardageRan holds the resulting yardage from the run play. (Gain or loss).
    #This is the value that eventually gets returned
    yardageRan = int(0)

    #This loop lets us re-prompt the user if they enter an invalid option.
    #Essentially, "restart if they have gained no yards."
    while(yardageRan == 0):

        #INTRO TEXT
        print("You have selected RUN.\n")
        print("There are two types of runs in this game: RISKY, or CONSERVATIVE.")
        print("What type of run would you like to perform? (Enter BACK if you have changed your mind about running.)")
        
        #Prompt for selection
        match(input("Enter RISKY, CONSERVATIVE, or BACK: ").upper()):

            #The RISKY run has a 30% chance of success.
            #On a success, the player gains 1-10 yards.
            #On a failure, the player loses 1-5 yards
            case "RISKY":
                print("\nYou have chosen to perform a risky run...")
                if(random.randrange(0, 101) <= 30):
                    yardageRan = random.randrange(1, 11)
                    print("You gained", str(yardageRan), "yard(s).\n")
                    
                else:
                    yardageRan = random.randrange(-5, 0)
                    print("You lost", str(abs(yardageRan)), "yard(s).\n")

                return yardageRan

            #The CONSERVATIVE run has a 60% chance of success.
            #On a success, the player gains 1-5 yards.
            #On a failure, the player gains no yards 
            case "CONSERVATIVE": 
                print("\nYou have chosen to perform a conservative run...")
                if(random.randrange(0, 101) <= 60):
                    yardageRan = random.randrange(1, 6)
                    print("You gained", str(yardageRan), "yard(s).\n")
                else:
                    print("You gained no yards.\n")

                return yardageRan

            #Typing BACK returns the string "BACK" which is handeled back in the game() function.
            case "BACK":
                print("Okay, returning to the main menu.\n")
                return("BACK")

            #Else, tell the player that their selection is invalid
            case _:
               print("\nThat is not a valid option here. Try again.\n")

#
#THE kick() function
#Params: yardage - An int representing the players current distance to the end zone.
#Returns: An int 0-2, representing the result of the kick.
#RETURN VALUE KEY:
#----------------
#(0) A return value of 0 is an unsuccessful kick.
#(1) A return value of 1 is a successful kick.
#(2) A return value of 2 is a "too far" result.
#
#This function is simple.
#(1) It takes the yardage from the param.
#(2) If the yardage is more than 50, it returns 2, stating it's too far.
#(3) If the yardage is less than or equal to 50, it continues.
#(4) The program generates a random number 1-10
#(5) If 2*yardage is less than that random number, the kick is good, so it returns 1
#(6) Else, it returns the default value of 0, for no good.
def kick(yardage):

    #goodKick defines the int that will be returned
    goodKick = int(0)

    if(yardage <= 50):
        if(random.randrange(1, 11) > (yardage*2)):
            goodKick = 1
    else:
        goodKick = 2

    return goodKick

#
#THE passBall() FUNCTION
#Params: None
#Returns: An int representing the yardage gained
#
#The passBall() function calculates the amount of yards gained from a pass play.
#It prompts the player to choose between 2 types of pass:
# * The low-risk, low-reward "SHORT" pass
# * The high-risk, high-reward "LONG" pass
#The player can also choose to go back to the main game menu.
#
def passBall():

    #The yardagePassed holds the resulting yardage from the run play. (Gain or loss).
    #This is the value that eventually gets returned.
    yardagePassed = int(0)

    #This loop lets us re-prompt the user if they enter an invalid option.
    #Essentially, "restart if they have gained no yards."
    while(yardagePassed == 0):

        #INTRO TEXT
        print("You have selected PASS.\n")
        print("There are two types of passes in this game: SHORT passes, or LONG passes.")
        print("What type of pass would you like to perform? (Enter BACK if you have changed your mind about passing.)")

        #Prompt for selection
        match(input("Enter SHORT, LONG, or BACK: ").upper()):

            #The SHORT pass has a 50% chance of success.
            #On a success, the player gains 1-5 yards.
            #On a failure, the player fumbles and get no yards
            case "SHORT":
                print("\nYou have chosen to perform a short pass...")
                if(random.randrange(0, 101) <= 50):
                    yardagePassed = random.randrange(1, 6)
                    print("You gained", str(yardagePassed), "yard(s).\n")
                    return yardagePassed
                else:
                    print("Your pass was unsuccessful.\n")
                    return yardagePassed
            
            #The LONG pass has 30% chance of success.
            #On a success, the player gains 1-50 yards.
            #On a failure, the player fumbles and get no yards.
            case "LONG":
                print("\nYou have chosen to perform a long pass...")
                if(random.randrange(0, 101) <= 30):
                    yardagePassed = random.randrange(1, 51)
                    print("You gained", str(yardagePassed), "yard(s).\n")
                    return yardagePassed
                else:
                    print("Your pass was unsuccessful.\n")
                    return yardagePassed

            #Typing BACK returns the string "BACK" which is handeled back in the game() function.
            case "BACK":
                print("Okay, returning to the main menu.\n")
                return "BACK"

            #Else, tell the player that their selection is invalid
            case _:
               print("\nThat is not a valid option here. Try again.\n")

#
#THE comTurn() FUNCTION
#Params: None
#Returns: An int representing the points the computer gained on their turn
#
#Simply generates a random number 0-2 and that determines the outcome of the computer's turn.
def comTurn():
    match (random.randrange(0,3)):
        case 0:
            print("\nThe computer didn't score any points!\n")
            return 0
        case 1:
            print("\nThe computer got a field goal!\n")
            return 3
        case 2:
            print("\nThe computer got a touchdown!\n")
            return 6

#
#THE game() FUNCTION
#Params: None
#Returns: None
#
#The game() function represents the main logic of the football game.
#
def game():

    #gameRunning defines a boolean variable that represents if the main loop is running.
    #Quitting the game sets this to false, allowing the main game loop to exit.
    gameRunning = bool(True)

    #yardage represents the amount of yards until the end zone.
    yardage = int(80)

    #yardageGainedOnThisSetOfDowns is self explanatory.
    #This is needed so that we can do a turnover if the user fails to gain 10 yards in 4 downs.
    yardageGainedOnThisSetOfDowns = int(0)

    #currentDown is a number 1-4 representing what down the player is currently on
    currentDown = int(1)

    #userScore stores the user's score.
    userScore = int(0)

    #comScore stores the computer's score
    comScore = int(0)

    #posessionsPerTeam stores the amount of posessions for each team.
    #This variable counts up with each computer turn.
    posessionsPerTeam = int(0)

    #INTRODUCTORY TEXT
    print("Welcome to the interactive terminal football game.")
    print("Our version of football ends after both teams have had 2 possessions.")
    print("You can RUN, KICK, PASS, or QUIT the program.\n")
    
    #MAIN GAME LOOP
    while gameRunning:

        #At the beginning of each player turn, check to see if they have gained 10 yards on this set of downs.
        #If so, set the currentDown back to 1, and the yardage gained since the last down back to 0.
        if yardageGainedOnThisSetOfDowns >= 10:
            yardageGainedOnThisSetOfDowns = 0
            currentDown = 1

        #The events in this "if" statement execute whenever there is a turnover or touchdown.
        if currentDown == 5 or yardage<=0:

            #If we have used-up 4 downs, tell the player that posession is changing due to this fact.
            if currentDown == 5:
                print("\nTURNOVER\n")
                print("You failed to clear 10 yards in 4 downs.")
                print("(You moved the ball a total of", yardageGainedOnThisSetOfDowns, "yard(s) since the downs last reset.)")
                print("It's the computer's turn now.\n")
            
            #If the yardage is 0 or less, this means that we have reached the end zone.
            #Let the player know, and then award them 6 points.
            if yardage <= 0:
                print("\nTOUCHDOWN!\n")
                print("Your team has gained 6 points!\n")
                print("It's the computer's turn now.\n")
                userScore += 6
            
            #Now, regardless of whether it is a touchdown or turnover, we must let the computer have a turn.
            #Run the comTurn function to get a computer player score.
            comPointsThisTurn = comTurn()

            #Add the score from this computer turn to the computer's overall score.
            comScore += comPointsThisTurn

            #If the computer got a touchdown or a field goal, start the player at the 35.
            #If they didn't score, place the player at a random location between the yardage at their turn and the 10.
            #(This represents the computer having moved the ball down the field.)
            if comPointsThisTurn == 3 or comPointsThisTurn == 6:
                yardage = 65
            else:
                yardage = random.randrange(yardage, 91)

            #A player turn and a computer turn having happened, we now increase the posessions count by one.
            posessionsPerTeam += 1

            #Reset the yardage and downs for a new player turn.
            yardageGainedOnThisSetOfDowns = 0
            currentDown = 1
        
        #If both sides have had 2 turns, the game is over.
        #Declare this fact to the player, and tell them the final score, as well as who won.
        if posessionsPerTeam == 2:
            print("That's game!")
            print("The final score was", userScore,"player,", comScore, "computer.")
            if userScore > comScore:
                print("Your team won!\n")
            elif userScore == comScore:
                print("You tied the computer.\n")
            else:
                print("You lost!\n")
            gameRunning = False

        #The main body of the player's play is in this else statement.
        #At the start of each play, remind the player of the score, the yards to the end zone, and the down.
        else:
            print("Your team has posession! You currently have", yardage, "yards to go; your team is on down number", currentDown, ".")
            print("The score is", userScore, " you -", comScore, "them.")
            print("What would you like to do?")
            match (input("Enter RUN, KICK, PASS, or QUIT: ").upper()):
                
                #If the player decides to run, call the "run()" function, which returns a number of yards run.
                #The "run()" function may also return "BACK", which causes the match statement to exit without doing anything.
                #This allows the player to cancel their run.
                #If it's NOT a response of "BACK", we do 3 things...
                #
                #(1) Subtract the yardage gained from the yardage counter
                #(2) Add the yardage gained to the yardageOnThisSetOfDowns
                #(3) Increment the current down
                case "RUN":
                    print("\n")
                    yardageThisRun = run()
                    if yardageThisRun != "BACK":
                        yardage -= yardageThisRun
                        yardageGainedOnThisSetOfDowns += yardageThisRun
                        currentDown+=1

                #If the player decides to kick, call the "kick()" function, which returns a number 0-2
                #If the player attempts to kick from further than the 50 yard line, it fails.
                #
                #RETURN VALUE KEY:
                #----------------
                #(0) A return value of 0 is an unsuccessful kick. The player gets a message and a down is consumed.
                #(1) A return value of 1 is a successful kick. The player gets a message, their score goes up, and the computer goes.
                #(2) A return value of 2 is a "too far" results in a message, and exits without consuming a down.
                case "KICK":
                    print("\n")
                    match kick(yardage):
                        case 0:
                            print("NO GOOD!")
                            print("The field goal was unsuccessful.\n")
                            currentDown+=1

                        #This is the case that the field goal succeeds. Also calls "comTurn()" for a computer turn.
                        #The code in this section is very similar to the touchdown case at the top of the loop.
                        #It's most of the same operations.
                        case 1:
                            print("IT'S GOOD!")
                            print("The field goal was successful. You have been awarded 3 points!\n")
                            comPointsThisTurn = comTurn()
                            comScore += comPointsThisTurn
                            if comPointsThisTurn == 3 or comPointsThisTurn == 6:
                                yardage = 65
                            else:
                                yardage =random.randrange(yardage, 91)

                            posessionsPerTeam += 1
                            yardageGainedOnThisSetOfDowns = 0
                            currentDown = 1

                        case 2:
                            print("You are too far to try for a field goal. Try something else.\n")
                        
                        #In the impossible case that the function returns something other than our expected numbers, crash gracefully
                        case _:
                            print("The program has encountered a unexpected error, and must stop.\n")
                            gameRunning = False

                #If the player decides to pass, call the "pass()" function, which returns a number of yards gained.
                #The "pass()" function may also return "BACK", which causes the match statement to exit without doing anything.
                #If the response is not "BACK", do the following 3 things...
                #
                #(1) Subtract the yardage gained from the yardage counter
                #(2) Add the yardage gained to the yardageOnThisSetOfDowns
                #(3) Increment the current down
                case "PASS":
                    print("\n")
                    yardageThisPass = passBall()
                    if yardageThisPass != "BACK":
                        yardage -= yardageThisPass
                        yardageGainedOnThisSetOfDowns += yardageThisPass
                        currentDown += 1

                #If the player enters "QUIT", exit the game.
                case "QUIT":
                    print("\n")
                    gameRunning = False

                #Else, tell them the command wasn't allowed.
                case _:
                    print("That command was unrecognized; please try again.")

    #Upon exiting, print the exit message and return.
    print("Goodbye! Thanks for playing!")
    return()

#Run the main game.
game()