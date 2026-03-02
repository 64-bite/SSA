#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

void handle_sigxfsz(int sig) {
	printf("File size limit exceeded\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Program need two arguments\n");
		return 1;
	}

	signal(SIGXFSZ, handle_sigxfsz);

	FILE *src = fopen(argv[1], "rb");
	if (src == NULL) {
		printf("Cannot open file %s for reading\n", argv[1]);
		return 1;
	}

	FILE *dst = fopen(argv[2], "wb");
	if (dst == NULL) {
		printf("Cannot open file %s for writing\n", argv[2]);
		fclose(src);
		return 1;
	}

	char buffer[4096];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
		size_t bytes_written = fwrite(buffer, 1, bytes_read, dst);

		if (bytes_written < bytes_read) {
			if (errno == EFBIG) {
				printf("File size limit exceeded\n");
			} else {
				printf("Write error occurred\n");
			}
			fclose(src);
			fclose(dst);
			return 1;
		}
	}

	fclose(src);
	fclose(dst);
	return 0;
}
