#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	unsigned char dani[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
	int deskryptor;

	deskryptor = open("fail.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (deskryptor == -1) {
        	perror("Помилка відкриття файлу");
        	return 1;
	}

	if (write(deskryptor, dani, sizeof(dani)) != sizeof(dani)) {
        	perror("Помилка запису");
        	close(deskryptor);
        	return 1;
    	}

	printf("У файл успішно записано %zu байтів.\n", sizeof(dani));

	if (lseek(deskryptor, 3, SEEK_SET) == -1) {
        	perror("Помилка позиціонування");
        	close(deskryptor);
        	return 1;
    	}

	unsigned char bufer[4];

	ssize_t prochytano = read(deskryptor, bufer, 4);

	if (prochytano == -1) {
        	perror("Помилка читання");
        	close(deskryptor);
        	return 1;
    	}

	printf("Прочитано %zd байтів. Вміст буфера:\n", prochytano);
	for (int i = 0; i < prochytano; i++) {
        	printf("%d ", bufer[i]);
    	}
	printf("\n");
	close(deskryptor);
	unlink("fail.bin");
	return 0;
}
