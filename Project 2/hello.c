#include<stdio.h>

int main(){
	int local_uninit[1000];
	int local_init[1000] = {1};
	printf("Un: %d\n Init: %d\n", local_uninit[500], local_init[0]);
	return 0;
}
