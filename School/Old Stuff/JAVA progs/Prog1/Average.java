/*
 * program name: Average Calculator
 * Programmers name: Caleb Ruby, Adir Turgemen, Caleb Rachocki, Ryan Miller
 * Course title: Technical Computing using Java
 * Course Number: CSMC3320
 * Emails: tur28711@pennwest.edu, rub4133@pennwest.edu, rac3146@pennwest.edu, mil0780@pennwest.edu
 * Date: 1/22/2024
 * Programs purpose: To calculate the average of a set of numbers ranging from 0.0-100.0
 */
import java.io.*;
public class Average
{

	public static void main(String[] args) throws IOException 
	{
		// Set Bufferreader	
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
		//set varibel
		String line;
		double i = 0;
		double total=0;
		double count= 0;
		double average = 0;
		
		//while loop to prompt the user to enter a grade and assign it to i
		while(i>=0 && i<=100)
		{
			System.out.print("\nEnter a grade:");
			System.out.flush();
			line = stdin.readLine();
			i = Double.parseDouble(line);
			
		// Prompt the user with the its entry 
			System.out.println("You entered: " +i+ "\n");
			
		// If statment to include only grades between 0-100	
			if(i>=0 && i<=100)
			{
				count++;
				total = total + i;
			}
			
			// catch out of range numbers and prompt the user
			else
			{
				System.out.println("Number outside of bounds entered, exiting entry process.\n");
			}
			
				
		}
		
		// calculate average
		average = total/count;
		
		// Test if we have division by 0 or infinite number
			boolean num = Double.isNaN(average);
       		boolean infinite = Double.isInfinite(average);
        // prompt the user that the the average is invalid because it's not a number
       		if(num)
        	{
            		System.out.println("Average is invalid: Not-a-Number ");
        	}
        // prompt the user that the average is invalid because it's an infinite number
        	else if(infinite)
        	{
            		System.out.println("Average is invalid: Infinite ");
        	}
        // prompt the user with the average result, total of all grades entered, and number of grades enter
        	else
        	{
	        	System.out.println("Average: " +average);
				System.out.println("Total of all grades: "+total);
				System.out.println("Number of grades entered: "+count);
        	}
	}
}