#include <stdio.h>

float add(float a, float b);
float subtract(float a, float b);
bool greaterThan(float a, float b);

int main(int argc, char *argv[])
{

    return 0;
}

// Adds two float values
// Adds b to a
float add(float a, float b) {
	return a + b;
}

// Substracts two float values
// Subtracts b from a
float subtract(float a, float b) {
	return a - b;
}

// Checks if value a is greater than value b
// Taks two float values and returns a boolean value
bool greaterThan(float a, float b) {
	return a > b;
}
