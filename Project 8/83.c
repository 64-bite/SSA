#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROZMIR 10000

unsigned long long kilkist_porivnian = 0;

int porivniannia(const void *a, const void *b) {
	kilkist_porivnian++;
	int znachennia1 = *(const int *)a;
	int znachennia2 = *(const int *)b;
	if (znachennia1 < znachennia2) return -1;
	if (znachennia1 > znachennia2) return 1;
	return 0;
}

int chy_vidsortovano(int masyv[], int rozmir) {
	for (int i = 0; i < rozmir - 1; i++) {
        	if (masyv[i] > masyv[i + 1]) return 0;
	}
	return 1;
}

int main() {
	int masyv[ROZMIR];
	srand(time(NULL));

	for (int i = 0; i < ROZMIR; i++) masyv[i] = rand() % ROZMIR;
	kilkist_porivnian = 0;
	qsort(masyv, ROZMIR, sizeof(int), porivniannia);
	printf("Випадкові числа:\n");
	printf("Порівнянь: %llu | Відсортовано: %s\n\n", kilkist_porivnian, chy_vidsortovano(masyv, ROZMIR) ? "Так" : "Ні");

	for (int i = 0; i < ROZMIR; i++) masyv[i] = i;
	kilkist_porivnian = 0;
	qsort(masyv, ROZMIR, sizeof(int), porivniannia);
	printf("Вже відсортовані числа:\n");
	printf("Порівнянь: %llu | Відсортовано: %s\n\n", kilkist_porivnian, chy_vidsortovano(masyv, ROZMIR) ? "Так" : "Ні");

	for (int i = 0; i < ROZMIR; i++) masyv[i] = ROZMIR - i;
	kilkist_porivnian = 0;
	qsort(masyv, ROZMIR, sizeof(int), porivniannia);
	printf("Відсортовані у зворотному порядку:\n");
	printf("Порівнянь: %llu | Відсортовано: %s\n\n", kilkist_porivnian, chy_vidsortovano(masyv, ROZMIR) ? "Так" : "Ні");

	for (int i = 0; i < ROZMIR; i++) masyv[i] = 777;
	kilkist_porivnian = 0;
	qsort(masyv, ROZMIR, sizeof(int), porivniannia);
	printf("Всі числа однакові:\n");
	printf("Порівнянь: %llu | Відсортовано: %s\n\n", kilkist_porivnian, chy_vidsortovano(masyv, ROZMIR) ? "Так" : "Ні");

	return 0;
}
