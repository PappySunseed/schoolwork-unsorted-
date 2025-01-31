#include <stdio.h>
#include <sys/types.h>
#include <time.h>



main()
{
//makes use of time functions
	time_t now = time(NULL);
	struct tm *localTime = localtime(&now);

//real-time clock vars
	int h, m, s;
	h = localTime -> tm_hour;
	m = localTime -> tm_min;
	s = localTime -> tm_sec;

//char array using c library specifiers. Specifiers found on "https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm"
	char q[100];
	strftime(q, 100, "%A - %B %d, %Y", localTime);	


/*											Testing

	char *string_now = ctime(&now);
	
	printf("%s", string_now);
	
*/

	
	
	
	
	
//outputs the current day, month, day of the month, year, and current-time
	printf("\rToday is %s. Current Time is: \n%02d:%02d:%02d",q, h, m, s);

}
