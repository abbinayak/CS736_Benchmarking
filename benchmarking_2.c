#include <sys/time.h>
#include <stdio.h>
unsigned long get_time();
int main(int nargs, char **args) {
//fprintf (stdout, "The current epoch time / ms: %ld\n", get_time());
//long start_time = get_time();
int i;
unsigned long best=1000000000000;
for (i = 0; i < 10000000; ++i){
long start_time = get_time();
fprintf (stdout, "Diff: It took %ld ms to count to 10^8.\n", \
get_time() - start_time);
if(get_time()-start_time <best)
	best = get_time()-start_time;
}
fprintf (stdout, "Best time: %ld\n",best);
return 0;
}
unsigned long get_time() {
struct timeval tv;
gettimeofday(&tv, NULL);
unsigned long ret = tv.tv_usec;
        ret /= 1000;
        ret += (tv.tv_sec * 1000);
return ret;
}
