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

	#define RETURNED_ERROR -1
void Receive_Char_Data(int socket_identifier, int size);
void Receive_Int_Data(int socket_identifier, int size);
void Send_Char_Data(int socket_id, char *data);
void Send_Int_Data(int socket_id, int data);
void header();
void loginConsole(int socket);

void login(int sockfd) {
	header();
	loginConsole(sockfd);

}

void header() {
	printf("\n\n===============================================================\n\n");
	printf("Welcome to the online ATM System");
	printf("\n\n===============================================================\n\n");
}

char* UserInput() {
	char *input = malloc(sizeof(char)*20);
	scanf("%s", input);
	size_t last = strlen(input) - 1;
	if (input[last] == '\n') input[last] = '\0';
	//while (getchar() != '\n')
	return input;
}

void loginConsole(int socket) {
	char username;
	int pin;
	char* input;

	printf("You are required to login with your registered Username and PIN\n\n");

	printf("Please enter your username -->");	

	input = UserInput();

	Send_Char_Data(socket, input);
	Receive_Char_Data(socket, ARRAY_SIZE);
	printf("Please enter your PIN -->");
	
	input = UserInput();

	Send_Int_Data(socket, atoi(input));
	
	Receive_Int_Data(socket, ARRAY_SIZE);
	
}


int main(int argc, char *argv[]) {
	int sockfd, numbytes, i=0;  
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; /* connector's address information */

	if (argc != 3) {
		fprintf(stderr,"usage: client_hostname port_number\n");
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


	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(atoi(argv[2]));    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, \
	sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	
	login(sockfd);

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

void Send_Char_Data(int socket_id, char *data) {
	char buff[1024];
	strcpy(buff, data);
	send(socket_id, buff, sizeof(char*) * 1024, 0);
}

void Send_Int_Data(int socket_id, int data) {
	long long converted_number = htonl(data);
	send(socket_id, &converted_number, sizeof(long long) * 1024, 0);
}

void Receive_Char_Data(int socket_identifier, int size) {
    
    int number_of_bytes, i;

	
	char *data = malloc(sizeof(char*) * 1024);


	if ((number_of_bytes=recv(socket_identifier, data, sizeof(char*) * 1024, 0))
	         == RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);			
	    
	}

	printf("Response from server: %s\n", data);

}

void Receive_Int_Data(int socket_identifier, int size) {
    
    int number_of_bytes, i;

	long long received_int = 0;
	if ((number_of_bytes=recv(socket_identifier, &received_int, sizeof(long long) * 1024, 0))
         == RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);	
	}
	long long result = ntohl(received_int);
	printf("Response from server: %lli\n", result);

}
