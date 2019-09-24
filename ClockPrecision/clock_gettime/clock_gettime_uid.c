#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
	struct timespec start,end;
	double best=1000000,diff;
	for(int i=1;i<1000000;i++){
		if(clock_gettime(CLOCK_MONOTONIC, &start)==-1)
		{
			perror("Error on clock gettime start);
			exit(1);
		}
		for(int j=1;j<3;j++){}
		//printf("my process ID is %d\n", getpid());
		getuid();
		if(clock_gettime(CLOCK_MONOTONIC, &end)==-1)
		{
			perror("Error on clock gettime end);
			exit(1);
		}
		diff = (end.tv_sec - start.tv_sec)*(10^9);
		diff+= (end.tv_nsec - start.tv_nsec);
		if(diff < best && diff>0) best = diff;
	}


	printf("Time taken by clock_gettime() to fetch getuid() is %f nanoseconds\n", best);
	return 0;
}
