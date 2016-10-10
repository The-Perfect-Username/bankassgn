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

struct session {
	char* username;
	char* password;
};

//void Send_Array_Data(int socket_id);

int char_in_str(const char* str, const char* n);
char** readFile(char* file);
void Send_Array_Data(int socket_id, char* data);
//void Send_Array_Data(void *args);
char* Receive_Char_Data(int socket_identifier, int size);

char* Receive_Login_Password(int socket_identifier, int size);
char* Receive_Login_Username(int socket_identifier, int size);

void Handle_Client(int);
char *global;

char *inner[4];
char buff[SIZE];
FILE *fp;
size_t nread;
int i = 0, j = 0;
struct session *user;
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
	char* c;
	while (1) {
		char* username = Receive_Login_Username(client_fd, 1024);
		Send_Array_Data(client_fd, username);
		char* pin = Receive_Login_Password(client_fd, 1024);
		Send_Array_Data(client_fd, pin);
		
		char** rf = readFile("active/Authentication.txt");
		int it = 0, ib = 0;
		while (it < 5) {
			char* red = rf[it];
			while (ib < 3) {
				printf("%s \n", rf);
				ib++;
			}
			ib = 0;
			it++;
		}
		
		exit(1);
	}

}


void Send_Array_Data(int socket_id, char* data) {
	//void *args
	//struct thread_params *params = args;
	
	//int socket_id = params->param_one;
	//char* array = global; //params->param_two;
	
	//free(params);

	send(socket_id, data, sizeof(char*) * 50, 0);
}

char* Receive_Char_Data(int socket_identifier, int size) {
    
    int number_of_bytes, i=0;
	char *array = malloc(sizeof(char*)*size);

	if ((number_of_bytes=recv(socket_identifier, array, sizeof(char*) * size, 0))
	         == RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);			
	    
	}
	// Prevents any empty data sent from the client 
	printf("Sent: %s \n", array);
	return array;
	
}

char* Receive_Login_Username(int socket_identifier, int size) {
    
    int number_of_bytes;
	char *array = malloc(sizeof(char*)*size);
	char *value = malloc(sizeof(char*)*size);

	if ((number_of_bytes=recv(socket_identifier, array, sizeof(char*) * size, 0))
	         == RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);			
	    
	}
	// Prevents any empty data sent from the client 
	if ((int)strlen(array) > 0) {
		value = array; 
		printf("Sent: %s \n", value);
	
	}
	return value;
}

char* Receive_Login_Password(int socket_identifier, int size) {
    
    int number_of_bytes;
	char *array = malloc(sizeof(char*)*size);
	char *value = malloc(sizeof(char*)*size);
	if ((number_of_bytes=recv(socket_identifier, array, sizeof(char*) * size, 0))
	         == RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);			
	    
	}
	// Prevents any empty data sent from the client 
	if ((int)strlen(array) > 0) {
		value = array;
		printf("Sent: %s \n", value);
	}
	return value;
}

char** readFile(char* file) {
	fp = fopen(file, "r");
	char **array = malloc(2000 * sizeof(char*));
	if (fp != NULL)
	{
		
		
		char line[128]; 
		char *token;

		while (fgets (line, sizeof line, fp) != NULL) 
		{
			token = strtok(line," \t");
			while(token != NULL)
			{
				
				// Checks to see if the current element is a space character
				if ((int)strlen(token) > 1) {
					inner[j] = token;
					//printf("inner[%d] = %s \n", j, inner[j]);					
				} else {
					// Decrement by 1 to overwrite element occupied by space character
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
	
	return array;
}

int char_in_str(const char* str, const char* n) {
	char *c = strstr(str, n);
	int value = 0;
	
	if (c) {
		value = 1;
	}
	
	return value;
}

