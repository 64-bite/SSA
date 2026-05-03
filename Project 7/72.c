#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf(S_ISDIR(mode) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf("  ");
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Не вдалося відкрити директорію");
        return 1;
    }

    printf("Права  Розмір (Байт)  Ім'я файлу\n");
    printf("--------------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            print_permissions(file_stat.st_mode);
            printf("%10ld  %s\n", file_stat.st_size, entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}
