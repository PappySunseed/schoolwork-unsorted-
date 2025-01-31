##exercises 1, 5 ,6 
#Assume a file containing a series of integers is named numbers.txt and exists on the com-
#puter’s disk. Write a program that displays all of the numbers in the file. Assume a file containing a series of integers is named numbers.txt and exists on the com-
#puter’s disk. Write a program that reads all of the numbers stored in the file and calculates
#their total.
#6. Average of Numbers
#Assume a file containing a series of integers is named numbers.txt and exists on the
#computer’s disk. Write a program that calculates the average of all the numbers stored in
#the file.
def main():
    inp = open("numbers.txt",r)

    numCount = 0
    total = 0

    for line in inp:
        float (line)
        numCount+=1
        total += line
    
    avg = total/numCoun

    print("average", avg)