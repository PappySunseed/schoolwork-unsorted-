
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

#define SHMKEY 0x727

//The Student struct holds an entry for a single student's data.
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


int main(void) {
	
	int errorNum;
	int shm_id;		// ID storage
	struct Student *z;	// Z points to shared memory array

	
	// Call to get pre-existing shared memory
	shm_id = shmget( SHMKEY, 0, 0 );
	
	// Shmget error
	if (shm_id == -1) {
		printf("\nError: shmget() failed, errno %i\n", errorNum);
		perror( "shmget()" );
		exit(-1);
	}
	else
		printf(" \shmget() successful, shm_id = %i\n", shm_id);
	
	// Attach variable z to shared memory segment
	z = (struct Student *) shmat( shm_id, 0 , SHM_RDONLY);
	
	// Shmat error
	if((int) z == -1) {
		printf("Error: shmat() failed, errno %i\n", errorNum);
		perror( "shmat()" );
	}
	
	// Average GPA of users
		float avgpa;
		int n = 0; 
		while(n < 17)
		{
			avgpa = students[n].gpa + avgpa; 
			
			n++;
		}
		avgpa = avgpa/18;	
		printf("%.2f", avgpa);		//outputs the avg gpa rounded to 2 decimal places 
		
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
		int logct_3 = 0;
		int logct_2 = 0;
		int logct_1 = 0;
		int v = 0;
		
		int daysecs = 24*60*60;
		time_t now;
		
		while(v< 17)
		{
			if(now - students[j].lastLogin < daysecs)
			{
				logct_1++;
				break;
			}
			else if(now - students[j].lastLogin < 2*daysecs)
			{
				logct_2++;
				break;
			}
			else if(now - students[j].lastLogin < 3*daysecs)
			{
				logct_3++;
				break;
			}
						
			v++;
		}
		
		int totlogs = logct_1 + logct_2 + logct_3;
		
		printf("\n%d log-ins today, %d log-ins yesterday, and %d log-ins three days ago for a total of %d log-ins in the last 3 days combined.\n", logct_1, logct_2, logct_3, totlogs);
		
	// OPTIONAL - Sort and list users based on their last login time.
	
	// Detatch from shared memory
	shmdt((void *) z);
	
	return 0;
}
