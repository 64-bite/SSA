#include <stdio.h>
#include <stdlib.h>

int main(){
	int  *ptr = (int*)malloc(0);
	printf("%p\n", (void*)ptr);
	free(ptr);
	return 0;
}
