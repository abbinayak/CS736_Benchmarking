#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0) &&                           \
	defined(_POSIX_MONOTONIC_CLOCK)
#define HAS_CLOCK_GETTIME_MONOTONIC
#endif

int main(int argc, char *argv[]) {
	int ofds[2];
	int ifds[2];

	int size;
	char *buf;
	int64_t count, i, delta;
#ifdef HAS_CLOCK_GETTIME_MONOTONIC
	struct timespec start, stop;
#else
	struct timeval start, stop;
#endif

	if (argc != 3) {
		printf("usage: pipe_lat <message-size> <roundtrip-count>\n");
		return 1;
	}

	size = atoi(argv[1]);
	count = atol(argv[2]);

	buf = malloc(size);
	if (buf == NULL) {
		perror("malloc");
		return 1;
	}

	printf("message size: %i octets\n", size);
	printf("roundtrip count: %li\n", count);

	if (pipe(ofds) == -1) {
		perror("pipe");
		return 1;
	}

	if (pipe(ifds) == -1) {
		perror("pipe");
		return 1;
	}

	if (!fork()) { /* child */
		for (i = 0; i < count; i++) {

			if (read(ifds[0], buf, size) != size) {
				perror("read");
				return 1;
			}

			if (write(ofds[1], buf, size) != size) {
				perror("write");
				return 1;
			}
		}
	} else { /* parent */

#ifdef HAS_CLOCK_GETTIME_MONOTONIC
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime");
			return 1;
		}
#endif

		for (i = 0; i < count; i++) {

			if (write(ifds[1], buf, size) != size) {
				perror("write");
				return 1;
			}

			if (read(ofds[0], buf, size) != size) {
				perror("read");
				return 1;
			}
		}

#ifdef HAS_CLOCK_GETTIME_MONOTONIC
		if (clock_gettime(CLOCK_MONOTONIC, &stop) == -1) {
			perror("clock_gettime");
			return 1;
		}

		delta = ((stop.tv_sec - start.tv_sec) * 1000000000 +
				(stop.tv_nsec - start.tv_nsec));
#endif

		printf("average latency: %li ns\n", delta / (count * 2));
	}

	return 0;
}
