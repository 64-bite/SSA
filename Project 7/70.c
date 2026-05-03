#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rand_zero_to_one() {
	return (double)rand() / RAND_MAX;
}

double rand_zero_to_n(double n) {
	return ((double)rand() / RAND_MAX) * n;
}

int main() {
	srand(time(NULL));

	int count = 5;
	double n = 25.5;

	printf("--- (a) Випадкові числа у діапазоні [0.0, 1.0] ---\n");
	for (int i = 0; i < count; i++) {
		printf("%f\n", rand_zero_to_one());
	}

	printf("\n--- (b) Випадкові числа у діапазоні [0.0, %.2f] ---\n", n);
	for (int i = 0; i < count; i++) {
		printf("%f\n", rand_zero_to_n(n));
	}

	return 0;
}
