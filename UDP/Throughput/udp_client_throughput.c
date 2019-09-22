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
  
#define MAX 80
void error(char *msg)
{
    perror(msg);
    exit(0);
}
  
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
      double times_send;
      double times_recv,tstart,tsend,tend,min_time;
      double num = 3.2,num2=1000;
      char buff[MAX];
      int no_of_rounds = DATA_BLOCK/config.n_bytes;
      for (size_t i = 0; i < no_of_rounds; i++) {
	//printf("%ld",i);
        tstart = rdtscp();

    sendto(sockfd, buffer, config.n_bytes, 
        0, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
 	tsend = rdtsc();

    //printf("Hello message sent.\n");
 }
    read(sockfd, buff, sizeof(buff)); 
    tend = rdtsc();
    
   buffer[n] = '\0'; 
    //printf("Server : %s\n", buffer);

       times_send = tsend - tstart;
        times_recv = tend - tsend;
	min_time = times_send + times_recv;
    close(sockfd);

    printf("Minimum cycles:\n");
    printf("%f\n", min_time);
       printf("Min time:\n");
 printf("%f\n", (min_time/num));
printf("Min time:\n");
 printf("%f Mb/s\n", (config.n_bytes/(min_time/num))*num2); 
    free(buffer);
    return 0; 
} 
