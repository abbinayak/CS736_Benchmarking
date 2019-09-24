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
//#define MAXLINE 1024 

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

	int n, len; 
	// Timed send-receive loop
	uint64_t *times_send = malloc(sizeof(uint64_t) * N_ROUNDS);
	uint64_t *times_recv = malloc(sizeof(uint64_t) * N_ROUNDS);
	uint64_t min_time=10000000;
	uint64_t min_send=10000000;
	uint64_t min_recv=10000000;
	for (size_t i = 0; i < N_ROUNDS; i++) {
		
		uint64_t tstart = rdtscp();

		sendto(sockfd, buffer, config.n_bytes, 
				0, (const struct sockaddr *) &servaddr,  
				sizeof(servaddr)); 
		//printf("Hello message sent.\n");
		uint64_t tsend = rdtsc();

		n = recvfrom(sockfd, buffer, config.n_bytes,  
				0, (struct sockaddr *) &servaddr, 
				&len); 
		uint64_t tend = rdtsc();
		times_send[i] = tsend - tstart;
		times_recv[i] = tend - tsend;

		if(times_send[i]+times_recv[i]<min_time){ min_time =times_send[i]+times_recv[i];
			min_send = times_send[i];
			min_recv = times_recv[i];}
	}

	buffer[n] = '\0'; 
	//printf("Server : %s\n", buffer); 

	close(sockfd); 

	printf("Minimum cycles:\n");
	printf("(%" PRIu64 ")\n", min_time);
	free(times_send);
	free(times_recv);
	free(buffer);
	return 0; 
} 
