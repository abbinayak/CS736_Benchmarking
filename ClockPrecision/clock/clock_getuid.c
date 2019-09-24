#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define BILLION 1000000000
/*void fun() 
  { 
  for(int i = 0;i<20;i++)
  {
  printf("Hi");
  }
  } */

int main() 
{ 
	double best = 10000000000;
	/* clock_t clock(void) returns the number of clock ticks 
	   elapsed since the program was launched.To get the number  
	   of seconds used by the CPU, you will need to divide by  
	   CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical 
	   32 bit system.  */
	clock_t start, end; 
	for(int i = 0; i<10; i++)
	{
		/* Recording the starting clock tick.*/
		start = clock(); 

		getuid(); 

		// Recording the end clock tick. 
		end = clock(); 

		// Calculating total time taken by the program. 
		double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);  
		if(time_taken < best) best = time_taken;
	}
	printf("Time taken by the program to fetch getuid() is : %f nanoseconds\n", best*BILLION) ;  
	return 0;
} 
