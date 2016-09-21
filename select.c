#include <stdio.h>
#define EXIT_MENU 6
void accountMenu();
void accountInput(int input);
void lineBreak();
void divider();
int validateInput(int input);

int input_value;

int main(int argc, char *argv[])
{
	
	while(input_value != EXIT_MENU) {
		lineBreak();
		accountMenu();
		lineBreak();
		accountInput(input_value);
	}
	
    return 0;
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

void accountInput(int input) {
	int sub_input;

	printf("Select option 1-6 => ");
	scanf("%d", &input);
	input_value = input;
	
	if (validateInput(input)) {
		if (input != EXIT_MENU) {
			while (sub_input != 4) {
				lineBreak();
				printf("Please enter a selection \n");
				printf("<1> Savings Account \n");
				printf("<2> Loan Account \n");
				printf("<3> Credit Card  \n");
				lineBreak();
				printf("Enter your selection (4 to exit) => ");
				scanf("%d", &sub_input);
			}
		}

	} else {
		lineBreak();
		printf("Invalid selection. Please choose an option from the menu.");
		lineBreak();
	}
}

// Checks to see if the input is between 1 and 6
int validateInput(int input) {
	return input <= 6 && input >= 1;
}

// Adds line breaks between sections
void lineBreak() {
	printf("\n\n");
}

// Creates the main divider between sections of the menu/action
void divider() {
	lineBreak();
	printf("============================================================");
	lineBreak();
}
