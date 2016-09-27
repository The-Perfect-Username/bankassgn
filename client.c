#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

	#define MAXDATASIZE 100 /* max number of bytes we can get at once */

	#define ARRAY_SIZE 30


void Send_Array_Data(int socket_id, int *myArray) {
	int i=0;
	
	uint16_t network_byte_order_short;  
	
	for (i = 0; i < ARRAY_SIZE; i++) {
		
		network_byte_order_short = htons(myArray[i]);

		send(socket_id, &network_byte_order_short, sizeof(uint16_t), 0);
		
		printf("Array[%d] = %d\n", i, network_byte_order_short);		
	}
	fflush(stdout);
}



int main(int argc, char *argv[]) {
	int sockfd, numbytes, i=0, port_number;  
	char buf[MAXDATASIZE], *port;
	struct hostent *he;
	struct sockaddr_in their_addr; /* connector's address information */
	
	if (argc != 3) {
		fprintf(stderr,"usage: client_hostname port_number\n");
		exit(1);
	}

	if (argc != 2 && argc != 3) {
		fprintf(stderr,"usage: client_hostname\n");
		exit(1);
	}
	

	if ((he=gethostbyname(argv[1])) == NULL) {  /* get the host info */
		herror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	
	port = argv[2];
	port_number = atoi(port);


	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(port_number);    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, \
	sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	/* Create an array of squares of first 30 whole numbers */
	int simpleArray[ARRAY_SIZE] = {0};
	for (i = 0; i < ARRAY_SIZE; i++) {
		simpleArray[i] = i * i;
	}

	Send_Array_Data(sockfd, simpleArray);

	/* Receive message back from server */
	if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
		perror("recv");
		exit(1);
	}

	buf[numbytes] = '\0';

	printf("Received: %s",buf);

	close(sockfd);

	return 0;
}
