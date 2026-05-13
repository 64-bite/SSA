#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_access(const char *filepath) {
    int can_read = access(filepath, R_OK);
    int can_write = access(filepath, W_OK);

    printf("   [Читання]: %s | [Запис]: %s\n", 
           (can_read == 0) ? "ДОЗВОЛЕНО" : "ЗАБОРОНЕНО",
           (can_write == 0) ? "ДОЗВОЛЕНО" : "ЗАБОРОНЕНО");
}

int main() {
    const char *filepath = "/tmp/test_perms.txt";
    char cmd[256];

    printf("1. Створення файлу від імені поточного користувача...\n");
    FILE *f = fopen(filepath, "w");
    if (!f) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fputs("Тестові дані.\n", f);
    fclose(f);

    printf("   Статус доступу:\n");
    check_access(filepath);

    printf("\n2. Зміна власника на root та встановлення прав 600 (-rw-------)...\n");
    snprintf(cmd, sizeof(cmd), "sudo chown root:root %s && sudo chmod 600 %s", filepath, filepath);
    system(cmd);
    printf("   Статус доступу для звичайного користувача:\n");
    check_access(filepath);

    printf("\n3. Встановлення прав 644 (-rw-r--r--)...\n");
    snprintf(cmd, sizeof(cmd), "sudo chmod 644 %s", filepath);
    system(cmd);
    printf("   Статус доступу для звичайного користувача:\n");
    check_access(filepath);

    printf("\n4. Встановлення прав 666 (-rw-rw-rw-)...\n");
    snprintf(cmd, sizeof(cmd), "sudo chmod 666 %s", filepath);
    system(cmd);
    printf("   Статус доступу для звичайного користувача:\n");
    check_access(filepath);

    printf("\n5. Видалення тестового файлу...\n");
    snprintf(cmd, sizeof(cmd), "sudo rm %s", filepath);
    system(cmd);

    return 0;
}
