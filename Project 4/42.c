#include <stdio.h>
#include <stdlib.h>
int main(){
	int xa = 1000000;
	int xb = -3000;
	int num = xa * xb;
	printf("%zu\n", (size_t)num);

	void *ptr = (int*)malloc(num);

	if (ptr == NULL) {
		printf("Result: melloc can't returned memory!\n");
	} else {
		printf("Result: melloc is returned memory seccsesfuly\n");
		free(ptr);
	}
	return 0;
}
