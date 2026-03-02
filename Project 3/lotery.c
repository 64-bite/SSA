#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

static void setup_cpu_rlimit(int cpulimit) {
        struct rlimit rlim_new, rlim_old;

        if(cpulimit == -1)
                rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
        else
                rlim_new.rlim_cur = rlim_new.rlim_max = (rlim_t) cpulimit;

        if(prlimit(0, RLIMIT_CPU, &rlim_new, &rlim_old) == -1)
                perror("prlimit:cpu failed");

        printf("CPU rlimit [soft,hard] new [%ld:%ld]s : old [%ld:%ld]s (-1 = unlimited)\n", 
               (long)rlim_new.rlim_cur, (long)rlim_new.rlim_max, 
               (long)rlim_old.rlim_cur, (long)rlim_old.rlim_max);
}

static void lotery(int number, const char *text){
	printf("%s", text);
	int limit = (number * number) + 1 - number;
	for (int i = 0; i < number; i++) {
		int random_number = rand() % limit + number;
        printf("%d\n", random_number);
	}
}

int main() {
	srand(time(NULL));
	setup_cpu_rlimit(1);

	while (1) {
		lotery(7,"Lotery numbers from 7 to 49:\n");
		lotery(6,"Lotery numbers from 6 to 36:\n");
	}
    return 0;
}



