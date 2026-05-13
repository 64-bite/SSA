#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    char *home = getenv("HOME");
    if (home == NULL) {
        fprintf(stderr, "Помилка: не вдалося знайти домашній каталог.\n");
        return 1;
    }

    char orig_path[512], copy_path[512];
    snprintf(orig_path, sizeof(orig_path), "%s/my_test_file.txt", home);
    snprintf(copy_path, sizeof(copy_path), "%s/root_copy_file.txt", home);

    printf("1. Створення оригінального файлу...\n");
    FILE *f_orig = fopen(orig_path, "w");
    if (f_orig != NULL) {
        fputs("Це оригінальний текст.\n", f_orig);
        fclose(f_orig);
        printf("   [+] Файл створено: %s\n", orig_path);
    } else {
        perror("   [-] Помилка створення файлу");
        return 1;
    }

    printf("\n2. Копіювання файлу від імені root...\n");
    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "sudo cp %s %s", orig_path, copy_path);
    printf("   Виконуємо: %s\n", cmd);
    system(cmd);

    printf("\n   [i] Права доступу до створеної копії:\n   ");
    snprintf(cmd, sizeof(cmd), "ls -l %s", copy_path);
    system(cmd);

    printf("\n3. Спроба змінити копію файлу від імені звичайного користувача...\n");
    FILE *f_copy = fopen(copy_path, "a");
    if (f_copy == NULL) {
        printf("   [-] Результат: Відмовлено (Помилка: %s)\n", strerror(errno));
    } else {
        printf("   [+] Результат: Успіх!\n");
        fputs("Додатковий рядок від користувача.\n", f_copy);
        fclose(f_copy);
    }

    printf("\n4. Спроба видалити копію за допомогою команди rm...\n");
    snprintf(cmd, sizeof(cmd), "rm %s", copy_path);
    printf("   Виконуємо: %s\n", cmd);
    int rm_status = system(cmd);

    if (rm_status == 0) {
        printf("   [+] Результат: Файл успішно видалено!\n");
    } else {
        printf("   [-] Результат: Не вдалося видалити файл.\n");
    }

    remove(orig_path);

    return 0;
}
