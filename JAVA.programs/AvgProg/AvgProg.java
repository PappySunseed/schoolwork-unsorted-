/*
 * program name: Average Calculator
 * Programmers name: Caleb Ruby, Adir Turgemen, Caleb Rachocki
 * Date: 1/22/2024
 * Programs purpose: To calculate the average of a set of numbers ranging from 0.0-100.0
 */
import java.io.*;
public class AvgProg
{

	public static void main(String[] args) throws IOException 
	{
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
		String line;
		double i = 0;
		double total=0;
		double count= 0;
		double average = 0;
		while(i>=0 && i<=100)
		{
			System.out.print("\nEnter a grade:");
			System.out.flush();
			line = stdin.readLine();
			i = Double.parseDouble(line);
	
			System.out.println("You entered: " +i+ "\n");
			
			if(i>=0 && i<=100)
			{
				count++;
				total = total + i;
			}
			else
			{
				System.out.println("Number outside of bounds entered, exiting entry process.\n");
			}
			
				
		}
		average = total/count;
		System.out.println("Average: " +average);
	
		boolean num = Double.isNaN(average);
       		boolean infinite = Double.isInfinite(average);
        	if(num)
        	{
            		System.out.println("Average is invalid: Not-a-Number ");
        	}
        	if(infinite)
        	{
            		System.out.println("Average is invalid: Infinite ");
        	}
	}
}