#include <stdio.h>
#include <time.h>

int main() {
	struct timespec start_time;
	struct timespec finish_time;

	clock_gettime(CLOCK_MONOTONIC, &start_time);

    	for(int i = 0; i < 5; i++) {
        	printf("Hello world!\n");
    	}
	clock_gettime(CLOCK_MONOTONIC, &finish_time);

	double time_spent_ms = (finish_time.tv_sec - start_time.tv_sec) * 1000.0 + (finish_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

	printf("--------------------------\n");
	printf("Час виконання: %f мілісекунд\n", time_spent_ms);

	return 0;
}
