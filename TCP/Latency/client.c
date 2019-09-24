/*
 *  A client timing the roundtrip time of a message sent to a server multiple times.
 *  Usage: ./client.out -a <address> -p <port> -b <message_size (bytes)>
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
	double times_send,times_recv;
	double min_time=10000000;

	for (size_t i = 0; i < N_ROUNDS; i++) {

		uint64_t tstart = rdtscp();

		send_message(config.n_bytes, sockfd, wbuffer);
		uint64_t tsend = rdtsc();
		receive_message(config.n_bytes, sockfd, rbuffer);

		uint64_t tend = rdtsc();

		times_send = tsend - tstart;
		times_recv = tend - tsend;

		if(times_send+times_recv<min_time)
		{ 
			min_time =times_send+times_recv;
		}
	}
	close(sockfd);
	printf("Done!\n");
	printf("Minimum cycles: ");
	printf("%f\n", min_time);
	printf("Min time : %f\n", (min_time/3.2)/2);
	free(rbuffer);
	free(wbuffer);

	return 0;
}

