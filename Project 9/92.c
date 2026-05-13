#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	printf("Ініціалізація доступу до /etc/shadow через sudo...\n");
	printf("------------------------------------------------\n");

	pid_t pid = fork();

	if (pid < 0) {
                perror("Помилка під час виклику fork");
        	return 1;
    	} else if (pid == 0) {
        	execlp("sudo", "sudo", "cat", "/etc/shadow", NULL);
       		perror("Помилка виконання execlp");
        	exit(1);
    	} else {
        	int status;
        	waitpid(pid, &status, 0);

        	printf("------------------------------------------------\n");
        	if (WIFEXITED(status)) {
            		printf("Команда sudo завершилася з кодом: %d\n", WEXITSTATUS(status));
        	} else {
            		printf("Дочірній процес завершився нештатно.\n");
        	}
    	}

	return 0;
}
