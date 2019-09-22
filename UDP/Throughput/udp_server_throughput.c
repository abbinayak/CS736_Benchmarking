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
  
#define MAX 80
 void error(char *msg)
{
    perror(msg);
    exit(1);
}
 
// Driver code 
int main(int argc, char *argv[]) { 
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
   char buff[MAX]; 
      int no_of_rounds = DATA_BLOCK/config.n_bytes;
    for (i = 0; i < no_of_rounds; i++) {
	   printf("%d",i);
    n = recvfrom(sockfd, buffer, config.n_bytes,  
                0, ( struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0'; 
    //printf("Client : %s\n", buffer); 
    sendto(sockfd, buffer, config.n_bytes,  
        0, (const struct sockaddr *) &cliaddr, 
            len); 
}
    if(i==no_of_rounds)
    {
	    strcpy(buff,"Acknowledge message");
	write(sockfd, buff, sizeof(buff));
} 

    printf("Done!\n");  
    close(sockfd);
   

      
    return 0; 
} 
