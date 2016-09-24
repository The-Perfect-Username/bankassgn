#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024 /* read 1024 bytes at a time */
char *inner[3];
char buff[SIZE];
FILE *fp;
size_t nread;
int i = 0, j = 0;

int main() {


	fp = fopen("active/Accounts.txt", "r");

	if (fp != NULL)
	{
		char **array = malloc(2000 * sizeof(char*));
		
		char line[128]; /* or other suitable maximum line size */
		char *pch;

		while (fgets (line, sizeof line, fp) != NULL) /* read a line */
		{
			pch = strtok(line," ");
			while(pch != NULL)
			{
				
				// Checks to see if the current element is a space character
				if (strlen(pch) > 1) {
					inner[j] = pch;
					printf("inner[%d] = %s \n", j, inner[j]);					
				} else {
					// Decrememnt by 1 to overwrite element occupied by space character
					j--;
				}
				pch = strtok(NULL," ");
				j++;
			}
			
			array[i] = *inner;
			
			/*int c;
			for (c = 0; c < 3; c++) {
				printf("%s \n", inner[c]);
			}*/
			
			j = 0;
			i++;
		}
		fclose (fp);
	}
	else
	{
		perror("Accounts.txt"); /* why didn't the file open? */
	}
	
	return 0;
}

char scanLine() {

}



