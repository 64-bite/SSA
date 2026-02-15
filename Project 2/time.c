#include<stdio.h>
#include<time.h>

int main(){
	printf("Size of time_t: %ld\n", sizeof(time_t));
	time_t time = 0;
	printf("Time befour OVERFLOW: %s\n", asctime(gmtime(&time)));
	time_t timeO = time + 75878593403220801;
	printf("Time after OVERFLOW:  %s\n", asctime(gmtime(&timeO)));
	return 0;
}
