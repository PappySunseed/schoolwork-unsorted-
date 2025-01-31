#
# Program Name: Stock transaction Program   
# Programmers Names: Caleb Ruby, Austin Pringle, Caleb Rachocki
# Date: 1/20/2024
# Program Purpose: to act as a stock transaction calculator, taking values entered by the user and doing the proper calculations to display the appropriate data 
#

#inputs
username = input("what is your name: ")
numOfShares = int(input("How many shares are there: "))
purchasePrice = float(input("what is the purchase price per share: "))
salePrice = float(input("what is the sales price per share: "))
brokerPercentage = float(input("what is the percentage charged by the broker (type as a whole number): "))

#gets the brokerPercentage to the correct number to do the math correctly
#brokerPercentage = brokerPercentage * .01

#processing
cost = (numOfShares * purchasePrice)
commision1 = (brokerPercentage/100*cost)
total = (cost + commision1)
value = (salePrice * numOfShares)
commision2 = (brokerPercentage/100*value)
net = (value - commision2)
profit = (net - total)

#output
print(f'\n{username} bought {numOfShares} shares at ${purchasePrice} for a total cost of ${cost}')

print(f"The broker charged {brokerPercentage}% on the cost of the stocks, or ${commision1} for this purchase, making {username}'s total cost ${total}.")


print(f"\n{username} sold the stock at {salePrice} per share for a total of ${value}")

print(f"The broker again charged {brokerPercentage}% on the cost of the stocks, or ${commision2} for this sale.")

print(f"After paying the broker, {username} was left with ${net} from the sale. After factoring in the original cost, {username} profited ${profit}")