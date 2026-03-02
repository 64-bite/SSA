#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	void *ptr = NULL;
	int n =	10;
	int i = 0;
	while (i<=1){
		if (!ptr){
        		ptr = malloc(n);
		} else {
			printf("ptr != NULL\n");
		}
		strcpy((char*)ptr, "test");
		free(ptr);
		printf("%p\n",(void*)ptr);
		ptr = NULL;
		i++;
	}
	return 0;
}
