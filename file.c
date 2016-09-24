#include <stdio.h>

double add(double a, double b);
float subtract(float a, float b);
int greaterThan(float a, float b);

int main(int argc, char *argv[])
{
	double a, b;
	sscanf(argv[1],"%lf",&a);
	sscanf(argv[2],"%lf",&b);
	double t = add(a, b);
	printf("%f\n", t);
    return 0;
}

// Adds two float values
// Adds b to a
double add(double a, double b) {
	return a + b;
}

// Substracts two float values
// Subtracts b from a
float subtract(float a, float b) {
	return a - b;
}

// Checks if value a is greater than value b
// Taks two float values and returns a boolean value
int greaterThan(float a, float b) {
	return a > b;
}


