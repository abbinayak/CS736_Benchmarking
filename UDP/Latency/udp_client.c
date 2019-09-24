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

// Driver code 
int main(int argc, char *argv[]) { 
	int sockfd; 
	struct sockaddr_in servaddr; 
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
	uint64_t *times_send = malloc(sizeof(uint64_t));
	uint64_t *times_recv = malloc(sizeof(uint64_t));
	uint64_t min_time=10000000;
	
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
		times_send = tsend - tstart;
		times_recv = tend - tsend;

		if(times_send + times_recv <min_time){ 
			min_time =times_send +times_recv;
		}
	}

	buffer[n] = '\0'; 
	if(close(sockfd)==-1)
		error("ERROR closing socket"); 

	printf("Minimum cycles:\n");
	printf("(%" PRIu64 ")\n", min_time);
	printf("Min time : %f\n", (min_time/3.2)/2);
	free(times_send);
	free(times_recv);
	free(buffer);
	return 0; 
} 
