/*
*  Materials downloaded from the web. See relevant web sites listed on OLT
*  Collected and modified for teaching purpose only by Jinglan Zhang, Aug. 2006
*/


#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <errno.h>

	#define SIZE 1024
	#define ARRAY_SIZE 30  /* Size of array to receive */

	#define BACKLOG 10     /* how many pending connections queue will hold */

	#define RETURNED_ERROR -1



struct thread_params {
	int param_one;
	char* param_two;
};

//void Send_Array_Data(int socket_id);

int char_in_str(const char* str, const char* n);
void readFile(char* file);

void Send_Array_Data(void *args);
void Receive_Char_Data(int socket_identifier, int size);
void Handle_Client(int);
char *global;

char *inner[4];
char buff[SIZE];
FILE *fp;
size_t nread;
int i = 0, j = 0;

int main(int argc, char *argv[]) {

	/* Thread and thread attributes */
	pthread_t client_thread;
	pthread_attr_t attr;


	int sockfd, new_fd;  /* listen on sock_fd, new connection on new_fd */
	struct sockaddr_in my_addr;    /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	socklen_t sin_size;
	int i=0;

	/* Get port number for server to listen on */
	if (argc != 2) {
		fprintf(stderr,"usage: client port_number\n");
		exit(1);
	}

	/* generate the socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* generate the end point */
	my_addr.sin_family = AF_INET;         /* host byte order */
	my_addr.sin_port = htons(atoi(argv[1]));     /* short, network byte order */
	my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
		/* bzero(&(my_addr.sin_zero), 8);   ZJL*/     /* zero the rest of the struct */

	/* bind the socket to the end point */
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) \
	== -1) {
		perror("bind");
		exit(1);
	}

	/* start listnening */
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("server starts listnening ...\n");

	/* repeat: accept, send, close the connection */
	/* for every accepted connection, use a sepetate process or thread to serve it */
	while(1) {  /* main accept() loop */
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, \
		&sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n", \
			inet_ntoa(their_addr.sin_addr));


		//Create a thread to accept client
		Receive_Char_Data(new_fd, ARRAY_SIZE);

		struct thread_params *params = malloc(sizeof *params);
		
		params->param_one = new_fd;
    	params->param_two = global;
    	
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&client_thread, &attr, Handle_Client, new_fd); //new_fd

		pthread_join(client_thread,NULL);
		
		
		char* a = "Server: managed to send all data\n";
		if (send(new_fd, a, 40 , 0) == -1)
			perror("send");
	}

	close(new_fd);  
}

void Handle_Client(int client_fd) {
	while (1) {
		Receive_Char_Data(client_fd, 1024);
		Receive_Char_Data(client_fd, 1024);
	}


}


void Send_Array_Data(void *args) {
	
	struct thread_params *params = args;
	
	int socket_id = params->param_one;
	char* array = params->param_two;
	
	free(params);

	send(socket_id, array, sizeof(char*) * 50, 0);
}

void Receive_Char_Data(int socket_identifier, int size) {
    
    int number_of_bytes, i=0;
	char *array = malloc(sizeof(char*)*50);

	if ((number_of_bytes=recv(socket_identifier, array, sizeof(char*) * size, 0))
	         == RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);			
	    
	}
	
	printf("Sent: %s \n", array);
	global = array;

}

void readFile(char* file) {
	fp = fopen(file, "r");

	if (fp != NULL)
	{
		char **array = malloc(2000 * sizeof(char*));
		
		char line[128]; 
		char *token;

		while (fgets (line, sizeof line, fp) != NULL) 
		{
			token = strtok(line," \t");
			while(token != NULL)
			{
				
				// Checks to see if the current element is a space character
				if (strlen(token) > 1) {
					inner[j] = token;
					printf("inner[%d] = %s \n", j, inner[j]);					
				} else {
					// Decrememnt by 1 to overwrite element occupied by space character
					j--;
				}
				token = strtok(NULL," \t");
				j++;
			}
			
			array[i] = *inner;
			
			j = 0;
			i++;
		}
		fclose (fp);
	}
	else
	{
		perror(file); /* why didn't the file open? */
	}
}

int char_in_str(const char* str, const char* n) {
	char *c = strstr(str, n);
	int value = 0;
	
	if (c) {
		value = 1;
	}
	
	return value;
}

