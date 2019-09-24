// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <time.h>
#include <fcntl.h>
#include <netinet/udp.h>

#include "connection.h"

//#define PORT     8080 
//#define MAXLINE 1024 

// Driver code 
int main(int argc,char *argv[] ) { 
	int sockfd; 
	struct Config config = get_config(argc, argv);
	char *buffer = malloc(config.n_bytes);
	//char buffer[MAXLINE]; 
	//char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 

	// Filling server information 
	servaddr.sin_family    = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(config.port); 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
				sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	printf("Server ready, listening on port %d\n", config.port); 

	int len, n, i; 
	int last_seq = 0, bytes_recv=0;

	int bufferSize = 1000000000, packetSize = 0;
	udp_pkt.buf_len = config.n_bytes;

	while(packetSize < bufferSize)
		{
			printf("In while loop\n");	 
                	bytes_recv += recvfrom(sockfd, &udp_pkt, sizeof(udp_pkt),  
				0, ( struct sockaddr *) &cliaddr, 
				&len); 
		  // break it if there's a hole
		printf("Value of udp_pkt.seq: %d\n",udp_pkt.seq);
		printf("Value of last_seq: %d\n",last_seq);
    		if (udp_pkt.seq != (last_seq + 1))
       			 break;

		last_seq = udp_pkt.seq;

 	        packetSize += udp_pkt.buf_len;

   		 printf("Bytes recieved: %d\n", bytes_recv);
		}

		printf("Bytes not received\n");
	
	return 0; 
} 
