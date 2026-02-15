#include<stdio.h>
#include<stdlib.h>

int uninit;
int init = 1;

void text(){}
int main(){
	int i;
	int *heap = (int*)malloc(sizeof(int));
	printf("Text: %p\n", &text);
	printf("Data: %p\n", &init);
	printf("BSS%p\n", &uninit);
	if(heap) {
		printf("Heap %p\n", &heap);
		free(heap);
	}
	printf("The stack top is near %p\n", &i);
	return 0;
}
