#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define MAX 80
#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0) &&                           \
    defined(_POSIX_MONOTONIC_CLOCK)
#define HAS_CLOCK_GETTIME_MONOTONIC
#endif
#define DATA 1000000
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
uint64_t rdtscp(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
int main(int argc, char *argv[]) {
  int ofds[2];
 
 int ifds[2];
  char *buf;
   double times_send;
   int size;
  int64_t count, i;
  //uint64_t tsend, tend;
  double delta;
  char buff[MAX];
#ifdef HAS_CLOCK_GETTIME_MONOTONIC
  struct timespec start, stop;
#else
  struct timeval start, stop;
#endif

  if (argc != 2) {
    printf("usage: pipe_thr <message-size> \n");
    return 1;
  }

  size = atoi(argv[1]);
  //count = atol(argv[2]);

  buf = malloc(size);
  if (buf == NULL) {
    perror("malloc");
    return 1;
  }
 count = DATA/size;
  printf("message size: %i octets\n", size);
  printf("message count: %li\n", count);

  if (pipe(ofds) == -1) {
    perror("pipe");
    return 1;
  }
  if (pipe(ifds) == -1) {
    perror("pipe");
    return 1;
  }


  if (!fork()) {
    /* child */
//   tsend = rdtsc();
    for (i = 0; i < count; i++) {
      if (read(ifds[0], buf, size) != size) {
        perror("read");
        return 1;
      }
    }
      strcpy(buff,"Acknowledgement");
       if (write(ofds[1], buf, size) != size) {
        perror("write");
        return 1;
      }
    
  
//  uint64_t tend = rdtsc();
 // times_send= tend - tsend;
  // printf("Times : %f",times_send);
  // printf("throughput: %f Mb/s\n",(size/(times_send/3.2)*1000));
  }
  else {
/* parent */

#ifdef HAS_CLOCK_GETTIME_MONOTONIC
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
      perror("clock_gettime");
      return 1;
    }
/*    
#else
    if (gettimeofday(&start, NULL) == -1) {
      perror("gettimeofday");
      return 1;
    }
  */  
#endif

	 uint64_t tsend = rdtsc();
	 // count = DATA/size;
    for (i = 0; i < count; i++) {
      if (write(ifds[1], buf, size) != size) {
        perror("write");
        return 1;
      }

    }
    if (read(ofds[0], buff, strlen(buff)) != strlen(buff)) {
        perror("read");
        return 1;
      }

uint64_t tend = rdtsc();

#ifdef HAS_CLOCK_GETTIME
_MONOTONIC
    if (clock_gettime(CLOCK_MONOTONIC, &stop) == -1) {
      perror("clock_gettime");
      return 1;
    }

    delta = ((stop.tv_sec - start.tv_sec) * 1000000000 +
             (stop.tv_nsec - start.tv_nsec));
    //printf("Delta:%lf",delta);

#endif

    times_send= tend - tsend;
    printf("Times : %f",times_send);
    // printf("throughput: %li msg/s\n", (count * 1000000) / delta);
    //       (((count * 1000000) / times_send) * size * 8) / 1;
    printf("throughput: %f Mb/s\n",(size/(times_send/3.2)*10000));
   // printf("throughput: %f Mb/s\n",(size/delta)*1000);
}
  return 0;
}
