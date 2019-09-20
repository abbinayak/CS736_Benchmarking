#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int size;
  char *buf;
  int64_t count, i, delta;
  struct timeval start, stop;

  ssize_t len;
  size_t sofar;

  int ret;
  struct addrinfo hints;
  struct addrinfo *res;
  int sockfd;

  if (argc != 6) {
    printf("usage: tcp_lat <bind-to> <host> <port> <message-size> "
           "<roundtrip-count>\n");
    return 1;
  }

  size = atoi(argv[4]);
  count = atol(argv[5]);

  buf = malloc(size);
  if (buf == NULL) {
    perror("malloc");
    return 1;
  }

  printf("message size: %i octets\n", size);
  printf("roundtrip count: %li\n", count);

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me
  if ((ret = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
    return 1;
  }

  if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) ==
      -1) {
    perror("socket");
    return 1;
  }

  if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
    perror("bind");
    return 1;
  }

  if ((ret = getaddrinfo(argv[2], argv[3], &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
    return 1;
  }

  if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
    perror("connect");
    return 1;
  }

  gettimeofday(&start, NULL);

  for (i = 0; i < count; i++) {

    if (write(sockfd, buf, size) != size) {
      perror("write");
      return 1;
    }

    for (sofar = 0; sofar < size;) {
      len = read(sockfd, buf, size - sofar);
      if (len == -1) {
        perror("read");
        return 1;
      }
      sofar += len;
    }
  }

  gettimeofday(&stop, NULL);

  delta =
      (stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_usec - start.tv_usec) * 1000;

  printf("average latency: %li ns\n", delta / (count * 2));

  return 0;
}
