##exercises 1, 5 ,6 
#Assume a file containing a series of integers is named numbers.txt and exists on the com-
#puter’s disk. Write a program that displays all of the numbers in the file. Assume a file containing a series of integers is named numbers.txt and exists on the com-
#puter’s disk. Write a program that reads all of the numbers stored in the file and calculates
#their total.
#6. Average of Numbers
#Assume a file containing a series of integers is named numbers.txt and exists on the
#computer’s disk. Write a program that calculates the average of all the numbers stored in
#the file.

print("it's open")
inp = open("numbers.txt", 'r')

numCount = 0
total = 0

for line in inp:
   numCount+=1
   total += int(line)
    
avg = total/numCount

print("average", avg)