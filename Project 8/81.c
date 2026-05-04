#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd[2];

	if (pipe(fd) == -1) {
        	perror("pipe error");
        	return 1;
    	}

	int flags = fcntl(fd[1], F_GETFL, 0);
	fcntl(fd[1], F_SETFL, flags | O_NONBLOCK);

	size_t nbytes = 1024 * 1024;
	char *buffer = malloc(nbytes);

	if (buffer == NULL) {
        	perror("malloc error");
        	return 1;
    	}

	printf("Спроба записати %zu байтів у pipe...\n", nbytes);

	ssize_t count = write(fd[1], buffer, nbytes);

	if (count == -1) {
        	perror("write error");
    	} else {
        	printf("--- РЕЗУЛЬТАТ ---\n");
        	printf("Запитано (nbytes): %zu байтів\n", nbytes);
        	printf("Записано (count):  %zd байтів\n", count);
        	if (count < nbytes) {
            		printf("=> Відбувся частковий запис (short write)!\n");
        	} else {
            		printf("=> Записано все (неочікувано для pipe).\n");
        	}
    	}
	free(buffer);
	close(fd[0]);
	close(fd[1]);

	return 0;
}
