#include <stdio.h>
#include <stdlib.h>

int main() {
	void *ptr = malloc(16);
	printf("%p\n", ptr);
	ptr = realloc(ptr, 32);
	printf("%p\n", ptr);
	printf("------------------------------------------------------\n");
	free(ptr);

	void *ptr1  = malloc(16);
	printf("%p\n", ptr1);
	void *ptr2  = malloc(16);
	printf("%p\n", ptr2);
	ptr1 = realloc(ptr1, 32);
	printf("%p\n", ptr1);
	free(ptr2);
	free(ptr1);
	return 0;
}
