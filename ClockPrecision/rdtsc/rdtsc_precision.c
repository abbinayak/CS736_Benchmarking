#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#include "bench.h"

int main(int argc, char** argv)
{
	uint high;
	uint low;
	uint pid;
	ull start;
	ull end;
	uint val;
	uint best = (uint)-1;
	int x;

	for(x = 0;x < 100000;x++)
	{
		RDTSC(start);
		for(int j = 0; j<3; j++){}
		RDTSC(end);
	
		uint diff = (end - start);
		if(diff < best) best = diff;

	}

	printf("Cycles taken by rdtsc() : %u\n", best);
	return 0;
}	

