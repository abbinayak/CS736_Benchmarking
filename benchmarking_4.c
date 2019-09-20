#include <stdio.h>
#include <time.h>
#include <unistd.h>
 
  
// A sample function whose time taken to 
// be measured 
void fun() 
{ 
    
} 
  
int main() 
{ 
    /* int clock_gettime( clockid_t clock_id, struct  
     timespec *tp ); The clock_gettime() function gets 
     the current time of the clock specified by clock_id,  
     and puts it into the buffer  pointed to by tp.tp  
     parameter points to a structure containing  
     atleast the following members:     
     struct timespec { 
               time_t   tv_sec;        // seconds  
               long     tv_nsec;       // nanoseconds 
           }; 
    clock id = CLOCK_REALTIME, CLOCK_PROCESS_CPUTIME_ID,  
               CLOCK_MONOTONIC ...etc 
    CLOCK_REALTIME : clock  that  measures real (i.e., wall-clock) time. 
    CLOCK_PROCESS_CPUTIME_ID : High-resolution per-process timer  
                               from the CPU. 
    CLOCK_MONOTONIC : High resolution timer that is unaffected 
                      by system date changes (e.g. NTP daemons).  */
    struct timespec start, end; 
  
    // start timer. 
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); 
    // clock_gettime(CLOCK_REALTIME, &start); 
    clock_gettime(CLOCK_MONOTONIC, &start); 
  
    // unsync the I/O of C and C++. 
//    ios_base::sync_with_stdio(false); 
  
    fun(); 
  
    // stop timer. 
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); 
    // clock_gettime(CLOCK_REALTIME, &end); 
    clock_gettime(CLOCK_MONOTONIC, &end); 
  
    // Calculating total time taken by the program. 
    double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)); 
  
    printf("Time taken:%lf",time_taken);
    return 0; 
}
