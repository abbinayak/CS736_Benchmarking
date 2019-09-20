#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
	double time_spent = 0.0;
	double best=0.0;
	for(int i=1;i<100000;i++){
	clock_t begin = clock();
	printf("Hi");
	int a=5,c=2;
	printf("a=%d,c=%d",a,c);
	clock_t end = clock();
	
	time_spent+=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("Time difference is %lf seconds",time_spent);
	if(time_spent<best) best=time_spent*(10^9);
	}
	printf("Best time is %lf seconds",best);
	return 0;
}
