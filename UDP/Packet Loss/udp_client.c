// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <time.h>
#include <netdb.h> 
#include <fcntl.h>
#include <inttypes.h>
#include <ctype.h>
#include <netinet/udp.h>

#include "connection.h" 

//#define PORT 8080 
#define MAXLINE 1024 

// Driver code 
int main(int argc, char *argv[]) { 
	int sockfd; 
	//char buffer[MAXLINE]; 
	//char *hello = "Hello from client"; 
	struct sockaddr_in     servaddr; 
	struct hostent *server;

	struct Config config = get_config(argc, argv);

	// Init buffers
	char *buffer = malloc(config.n_bytes);

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	server = gethostbyname(config.address);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(config.port); 
	bcopy((char *)server->h_addr, 
			(char *)&servaddr.sin_addr.s_addr,
			server->h_length);

	udp_pkt.seq = 0;
	udp_pkt.buf_len = config.n_bytes;
	int writeSize = 0, len, bytes_sent, bufferSize = 1000000000;
	char lost[MAXLINE];
	char start[MAXLINE];	
	while(writeSize < bufferSize)
	{	

		udp_pkt.seq++;
		printf("Value of udp packet sequence: %d\n",udp_pkt.seq);
		//if(recvfrom(sockfd, (char *)lost, strlen(lost),  
		//0, (struct sockaddr *) &servaddr, 
		//&len))
		//
		//if(recvfrom(sockfd, (char *)start, strlen(start),  
		//0, (struct sockaddr *) &servaddr, 
		//&len))


		bytes_sent += sendto(sockfd, &udp_pkt, sizeof(udp_pkt),
				0, (const struct sockaddr *) &servaddr,
				sizeof(servaddr));
		printf("Bytes sent: %d\n", bytes_sent);
		writeSize += config.n_bytes;
		printf("Value of write size: %d\n",writeSize);                  



		//if(recvfrom(sockfd, (char *)lost, strlen(lost),
		//0, (struct sockaddr *) &servaddr,
		//&len))

		if(ch=='n')

		{
			printf("**********************IN CH = N LOOP*********************************************************\n");


			for(int i=last_seq+1;i<endpoint;i++){

				udp_pkt.seq=i;

				bytes_sent += sendto(sockfd, &udp_pkt, sizeof(udp_pkt),
						0, (const struct sockaddr *) &servaddr,
						sizeof(servaddr));
				printf("Bytes sent: %d\n", bytes_sent);

			}
		}

	}

	//printf("Hello message sent.\n");

	close(sockfd); 

	return 0; 
} 
