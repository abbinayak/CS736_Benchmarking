#include <stdio.h>
#include <time.h>
#include <unistd.h>


int main()
{
	struct timespec start,end;
	double best=1000000,diff;
	for(int i=1;i<1000000;i++){
		clock_gettime(CLOCK_MONOTONIC, &start);
		for(int j=1;j<3;j++){}
		//printf("my process ID is %d\n", getpid());
		getuid();
		clock_gettime(CLOCK_MONOTONIC, &end);
		diff = (end.tv_sec - start.tv_sec)*(10^9);
		diff+= (end.tv_nsec - start.tv_nsec);
		if(diff < best && diff>0) best = diff;
	}


	printf("Time elapsed is %f nanoseconds\n", best);
	return 0;
}
