
/*
 * Lab Assignment 4 - CLIENT
 * Caleb Rachocki, Caleb Ruby, Caleb Massey
 * Due 10/12/23
 *
*/

////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>			// Input / Output
#include <errno.h>			// Error handling
#include <sys/types.h>		// System Defined Types
//#include <sys/ipc.h>		// IPC permission structure
//#include <sys/shm.h>		// Shared Memory Facility defines
#include <math.h>

#define SHMKEY 0x727

/* The Student struct holds an entry for a single student's data. */
typedef struct
{
    char userID[9]; 	//null-terminated string with capacity 9
    char fullName[21]; 	//null-terminated string with capacity 21
    short age;
    float gpa;
    short active; 		// 0 == inactive, otherwise active
    time_t lastLogin; 	// the time the user last logged in
    int loginDuration; 	// total time the user has been logged into draco1 (in seconds)
} Student;				//in total the structure is 56 bytes in size

Student students[17];
/**/

int main(void) {
	
	int shm_id, i, *z;	// 'z' points to shared memory array
	
//	shm_id = shmget( SHMKEY, 0, 0 ); Not sure if needed
	
	// Average GPA of users
		float avgpa;
		int n = 0; 
		
		while(n < 17)
		{
			avgpa = students[n].gpa + avgpa; 
			
			n++;
		}
		
		avgpa = avgpa/18;
		
		//printf("%.2f", avgpa);		//outputs the avg gpa rounded to 2 decimal places 
		
		
		
		
	// Average age of users
		int avage;
		int k = 0; 
		
		while(k < 17)
		{
			avage = students[k].age + avage; 
			
			k++;
		}
		
		avage = avage/18;
	
	// Active users with FULL NAMES
		int j = 0;
		
		int active[17] = {0}; 
		
		while(j < 17)
		{
			if(students[j].active != 0 )
			{
				active[j] = 1;  
			}
					
			j++;
		}
		
		j = 0; 			//reset counting var
		while(j < 17)
		{
			if(active[j] == 1 )
			{
				printf("%s", students[j].fullName);	 
			}
				
			j++;
		}	
	
	
	// Login Statistics wothin the past 3 days; Do not include who was not logged in within that timeframe.
	// Ex. 7 users today, 10 yesterday, 4 two days ago
		
		
		
	// OPTIONAL - Sort and list users based on their last login time.
	
	return 0;
}
