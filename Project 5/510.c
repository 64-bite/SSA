#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *ptr = (char*)malloc(30 * sizeof(char));
	strcpy(ptr, "Hello error leak!");
	printf("Address of first object: %p\n", (void*)ptr);
	printf("Data of ptr: %s\n", ptr);

	char *ptr_new = ptr + 7;
	printf("Address of inner object: %p\n", (void*)ptr_new);
        printf("Data of ptr: %s\n", ptr_new);
	free(ptr_new);
	printf("This printf never happend!");

	return 0;
}
