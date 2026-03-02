#include <stdio.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>

void recursive_function(int counter) {
	if (counter % 1000 == 0) {
		printf("Глибина рекурсії: %d\n", counter);
	}
	recursive_function(counter + 1);
}

int main() {
	struct rlimit rl;

	if (getrlimit(RLIMIT_STACK, &rl) != 0) {
		printf("Error getrlimit: %s\n", strerror(errno));
		return 1;
	}

	printf("Initial soft limit: %lu byte\n", (unsigned long)rl.rlim_cur);
	printf("Initial hard limit: %lu byte\n", (unsigned long)rl.rlim_max);

	rl.rlim_cur = 1024 * 1024;

	if (setrlimit(RLIMIT_STACK, &rl) != 0) {
		printf("Error setrlimit: %s\n", strerror(errno));
		return 1;
	}

	printf("\nNew soft limit is seted up: %lu байт\n", (unsigned long)rl.rlim_cur);
	printf("Recursive is on. Waiting for segmentation fault...\n\n");

	recursive_function(1);
	return 0;
}
