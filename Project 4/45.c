#include <stdio.h>
#include <stdlib.h>

int main() {
	int *ptr = (int *)malloc(5 * sizeof(int));
	printf("%p\n", (void*)ptr);
	int *temp = (int *)realloc(ptr, (size_t)-1);
	printf("%p\n", (void*)temp);
	return 0;
}
