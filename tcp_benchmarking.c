#include <stdio.h>
#include <time.h>
#include <unistd.h>
/* Code snippet for measuring rtt with weighed moving average */
// rtt
double rtt = -1; // in s
double timeval_subtract(struct timeval *x, struct timeval *y)  
{  
double diff = x->tv_sec - y->tv_sec;  
    diff += (x->tv_usec - y->tv_usec)/1000000.0;  
return diff;  
}
/* measure rtt (with weighed moving average).
    cur_ts - start_ts is the time between request sent and first response socket.read() */
double measure_rtt(struct timeval *start_ts, struct timeval *cur_ts)
{
struct timeval result;
timeval_subtract(&result,cur_ts,start_ts);
double cur_rtt = result.tv_sec;
    cur_rtt += result.tv_usec/1000000.0;
if(rtt < 0)
    {
// first measurement
        rtt = cur_rtt;
    }
else
    {
// weighed moving average
        rtt = 0.8*rtt + 0.2*cur_rtt;
    }
return rtt;
}
