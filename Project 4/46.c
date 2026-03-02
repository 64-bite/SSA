#include <stdio.h>
#include <stdlib.h>

int main() {
	int *ptr = (int *)realloc(NULL, 100 * sizeof(int));

	if (ptr != NULL) {
		printf("Result: realloc create new memory space at address: %p\n", (void*)ptr);
	} else {
		printf("Can't create new memory space.\n");
		return 1;
	}
	int *new_ptr = (int *)realloc(ptr, 0);

	if (new_ptr == NULL) {
		printf("Result: realloc returned  NULL.\n");
	} else {
		printf("Result: realloc returned pointer: %p\n", (void*)new_ptr);
		free(new_ptr);
	}
	return 0;
}
