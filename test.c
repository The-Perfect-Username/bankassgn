#include <stdlib.h>
#include <stdio.h>
void main_menu();
void balance();
void withdrawal();
void deposit();
void depositInput();
void accountMenu();
char* accountOption(int account);
void accountOptions(char* array[3], int len);

int main(int argc, char* argv[]) {
	main_menu();
}

void main_menu() {
	int input;
	int a = 0;
	char line[10];
	do {
		accountMenu();
		fgets(line, sizeof line, stdin);
		a = sscanf(line, "%d",&input);
		if (a == 1 && input != 6) {
			if (input == 1) {
				balance();
			} else if (input == 2) {
				withdrawal();
			} else if (input == 3) {
				deposit();
			}
		} else {
			if (input == 6) {
				break;
			} else {
				fflush(stdin);
				printf("Invalid selection. Please select option from the menu!\n");
			}
		}
	} while(input != 6);

}

void balance() {
	int input;
	int a = 0;
	char line[10];
	do {
		char *array[3] = {"Savings Account", "Loan Account", "Credit Card"};
		accountOptions(array, 3);
		fgets(line, sizeof line, stdin);
		a = sscanf(line, "%d",&input);
		if (a == 1) {
			//char* d = accountOption(12);
			//printf("%s\n", d);
			break;
		} else {
			fflush(stdin);
			printf("0\n");
		}
	} while(input != 5);
}

void withdrawal() {
	int input;
	int a = 0;
	char line[10];
	do {
		char *array[2] = {"Savings Account", "Credit Card"};
		accountOptions(array, 2);
		fgets(line, sizeof line, stdin);
		a = sscanf(line, "%d",&input);
		if (a == 1) {
			//char* d = accountOption(12);
			//printf("%s\n", d);
			break;
		} else {
			fflush(stdin);
			printf("0\n");
		}
	} while(input != 5);
}

void deposit() {
	int input;
	int a = 0;
	char line[10];
	printf("The maximum daily deposit is $1000.00! \n\n");
	do {
		char *array[2] = {"Savings Account", "Credit Card"};
		accountOptions(array, 2);
		fgets(line, sizeof line, stdin);
		a = sscanf(line, "%d",&input);
		if (a == 1) {
			if (input == 1 || input == 2) {
				depositInput();
				break;
			} else {
				if (input == 3) {
					break;
				} else {
					printf("Invalid input! \n\n");
				}
			}
			
		} else {
			fflush(stdin);
			printf("0\n");
		}
	} while(input != 5);
}

void depositInput() {
	int input;
	int a = 0;
	char line[10];
	
	do {
		printf("Enter the amount to deposit => ");
		fgets(line, sizeof line, stdin);
		a = sscanf(line, "%d", &input);
		if (a == 1) {
			if (input > 1000) {
				printf("You cannot desposit more than $1000 in a single transaction! \n");
			} else {
				printf("Desposited $%d \n", input);
				break;
			}
		} else {
			fflush(stdin);
			printf("Invalid input \n");
		}
	
	} while(input != 3);
}

void accountMenu() {
	
	printf("Please enter a selection \n");
	printf("<1> Account Balance \n");
	printf("<2> Withdrawal \n");
	printf("<3> Deposit \n");
	printf("<4> Transfer \n");
	printf("<5> Transaction Listing \n");
	printf("<6> EXIT \n");
}

void accountOptions(char* array[3], int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("<%d> %s \n", i+1, array[i]);
	}
}

char* accountOption(int account) {
	if (account % 11 == 0) {
		return "Savings Account";
	} else if (account % 12 == 0) {
		return "Loan Account";
	} else if (account % 13 == 0) {
		return "Credit Card";
	}
}


