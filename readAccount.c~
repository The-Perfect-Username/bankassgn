#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024 /* read 1024 bytes at a time */

int char_in_str(const char* str, const char* n);

char *inner[4];
char buff[SIZE];
FILE *fp;
size_t nread;
int i = 0, j = 0;
void readFile(char* file);

int main() {

	readFile("active/Accounts.txt");
	
	
	return 0;
}

void readFile(char* file) {
	fp = fopen(file, "r");

	if (fp != NULL)
	{
		char **array = malloc(2000 * sizeof(char*));
		char line[128]; /* or other suitable maximum line size */
		char *token;

		while (fgets (line, sizeof line, fp) != NULL) /* read a line */
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
			i++;
			
		}
		free(array);
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

