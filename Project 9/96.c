#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void test_file_ops(const char *filepath) {
    printf("\n--- Тестування доступу до файлу: %s ---\n", filepath);

    FILE *f_read = fopen(filepath, "r");
    if (f_read) {
        printf("   [Читання]  : ДОЗВОЛЕНО\n");
        fclose(f_read);
    } else {
        printf("   [Читання]  : ВІДМОВЛЕНО (%s)\n", strerror(errno));
    }

    FILE *f_write = fopen(filepath, "a");
    if (f_write) {
        printf("   [Запис]    : ДОЗВОЛЕНО\n");
        fclose(f_write);
    } else {
        printf("   [Запис]    : ВІДМОВЛЕНО (%s)\n", strerror(errno));
    }

    if (access(filepath, X_OK) == 0) {
        printf("   [Виконання]: ДОЗВОЛЕНО\n");
    } else {
        printf("   [Виконання]: ВІДМОВЛЕНО (%s)\n", strerror(errno));
    }
}

int main() {
    char *home = getenv("HOME");
    if (home == NULL) {
        fprintf(stderr, "Помилка: не вдалося визначити домашній каталог.\n");
        return 1;
    }

    char cmd[512];

    printf("================ ДИРЕКТОРІЇ (ls -l) ================\n");

    printf("\n1. Домашній каталог (%s):\n", home);
    snprintf(cmd, sizeof(cmd), "ls -ld %s && ls -l %s | head -n 4", home, home);
    system(cmd);

    printf("\n2. Системні утиліти (/usr/bin):\n");
    system("ls -ld /usr/bin && ls -l /usr/bin | head -n 4");

    printf("\n3. Конфігурації системи (/etc):\n");
    system("ls -ld /etc && ls -l /etc | head -n 4");

    printf("\n================ ТЕСТУВАННЯ ОПЕРАЦІЙ ================\n");

    char my_file[512];
    snprintf(my_file, sizeof(my_file), "%s/temp_test_file.txt", home);
    FILE *tmp = fopen(my_file, "w");
    if(tmp) {
        fputs("Дані", tmp);
        fclose(tmp);
    }

    test_file_ops(my_file);
    remove(my_file);

    test_file_ops("/usr/bin/ls");
    test_file_ops("/etc/passwd");
    test_file_ops("/etc/shadow");

    printf("\n======================================================\n");
    return 0;
}
