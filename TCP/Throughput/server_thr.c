/*
 *  A server receiving and sending back a message multiple times.
 *  Usage: ./server_thr -b <NUM OF BYTES> -p <PORT NUMBER>
 */
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <string.h>
#include "connection.h"
#define MAX 80
void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd;
	struct Config config = get_config(argc, argv);
	uint8_t *buffer = malloc(config.n_bytes);
	struct sockaddr_in serv_addr, cli_addr;
	char buff[MAX];

	// Create listening socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		error("ERROR opening socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(config.port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}
	printf("Server ready, listening on port %d\n", config.port); 
	fflush(stdout);
	listen(sockfd, 5);
	socklen_t clilen = sizeof(cli_addr);

	// Accept connection and set nonblocking and nodelay
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		error("ERROR on accept");
	}
	fcntl(newsockfd, F_SETFL, O_NONBLOCK);
	int flag = 1;
	if(setsockopt(newsockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(int))==-1)
		error("ERROR setting socket");

	// Receive-send loop
	printf("Connection accepted, ready to receive!\n");
	int i;
	int rounds = DATA/config.n_bytes;
	for (i = 0; i < rounds; i++) {
		receive_message(config.n_bytes, newsockfd, buffer);
	}

	if(i==rounds)
	{
		strcpy(buff,"Acknowledge message");
		// and send that buffer to client
		write(newsockfd, buff, sizeof(buff));
	} 
	printf("Done!\n");

	// Clean state
	close(sockfd);
	close(newsockfd);

	return 0; 
}

