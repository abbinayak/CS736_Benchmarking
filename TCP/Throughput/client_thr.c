/*
 *  A client timing the roundtrip time of a message sent to a server multiple times.
 *  Usage: ./client_thr -a <address> -p <port> -b <message_size (bytes)>
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <inttypes.h>
#include <ctype.h>
#define MAX 80
#include "connection.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	struct Config config = get_config(argc, argv);

	// Init buffers
	uint8_t *rbuffer = malloc(config.n_bytes);
	uint8_t *wbuffer = malloc(config.n_bytes);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		error("ERROR opening socket");
	}
	server = gethostbyname(config.address);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(config.port);

	// Connect and set nonblocking and nodelay
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
		error("ERROR connecting");
	}
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	int flag = 1;
	if(setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(int))==-1)
		error("ERROR setting socket");

	printf("Connection successful! Starting...");
	fflush( stdout );

	// Timed send-receive loop
	double times_send;
	double times_recv,tstart,tsend,tend,min_time;
	char buff[MAX];
	int rounds = DATA/config.n_bytes; 
	for (size_t i = 0; i < rounds; i++) {
		tstart = rdtscp();

		send_message(config.n_bytes, sockfd, wbuffer);
		tsend = rdtsc();
	}
	if(read(sockfd, buff, sizeof(buff))==-1)
		error("ERROR reading from socket");   
	tend = rdtsc();

	times_send = tsend - tstart;
	times_recv = tend - tsend;
	min_time = times_send + times_recv;
	if(close(sockfd)==-1)
		error("ERROR closing socket");
	printf("Done!\n");
	printf("Cycles:\n");
	printf("%f\n", min_time);
	printf("Time:\n");
	printf("%f\n", (min_time/3.2));
	printf("Throughput:\n");
	printf("%f Mb/s\n", (config.n_bytes/(min_time/num))*1000); 
	free(rbuffer);
	free(wbuffer);

	return 0;
}

