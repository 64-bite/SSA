#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void test_fsize() {
	struct rlimit rl = {1024, 1024};
	setrlimit(RLIMIT_FSIZE, &rl);
	printf("Writing more than 1 Kb into test_limit.bin...\n");
	FILE *f = fopen("test_limit.bin", "wb");
	char buffer[2048] = {0};
    	fwrite(buffer, 1, sizeof(buffer), f); 
    	fclose(f);
    	exit(0);
}

void test_nofile() {
	struct rlimit rl = {10, 10};
	setrlimit(RLIMIT_NOFILE, &rl);

	printf("Opening file up to limit...\n");
	for (int i = 0; i < 20; i++) {
		int fd = open("/dev/null", O_RDONLY);
		if (fd < 0) {
			printf("Error on iteration %d: %s\n", i, strerror(errno));
			exit(1);
		}
	}
	exit(0);
}

void test_cpu() {
	struct rlimit rl = {1, 1};
	setrlimit(RLIMIT_CPU, &rl);

	printf("Turning on infinit cycle. Waiting for signal SIGXCPU...\n");
	while(1) {
	}
}

void test_stack(int depth) {
	if (depth == 1) {
	struct rlimit rl = {65536, 65536};
	setrlimit(RLIMIT_STACK, &rl);
	printf("Turning on deep recursion. Waiting for SIGSEGV...\n");
	}

	char buffer[1024] = {0};
	buffer[0] = depth;

	test_stack(depth + 1);
}
void wrapper_test_stack() {
	test_stack(1);
}

void run_test(void (*test_func)(), const char* test_name) {
	printf("\n=== Tets: %s ===\n", test_name);

	pid_t pid = fork();

	if (pid < 0) {
		perror("Error fork");
		return;
	}
	else if (pid == 0) {
        	test_func();
        	exit(0);
	}
	else {
		int status;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status)) {
			printf("Proces is finished by program %d.\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status)) {
			printf("Proces was killed by signal %d (%s).\n", 
			WTERMSIG(status), strsignal(WTERMSIG(status)));
		}
	}
}

int main() {
	printf("Starting complex test of limits...\n");

	run_test(test_fsize, "File size restrictions (RLIMIT_FSIZE)");
	run_test(test_nofile, "Restrictions on open files (RLIMIT_NOFILE)");
	run_test(test_cpu, "CPU time limit (RLIMIT_CPU)");
	run_test(wrapper_test_stack, "Stack limits (RLIMIT_STACK)");

	remove("test_limit.bin");

	printf("\nAll tests completed! The main program survived successfully.\n");
	return 0;
}
