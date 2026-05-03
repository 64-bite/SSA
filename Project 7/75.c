#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list_dir(const char *base_path, int level) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char path[1024];

    if ((dir = opendir(base_path)) == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);
        if (stat(path, &statbuf) == 0) {
            for (int i = 0; i < level; i++) {
                printf("  "); 
            }

            if (S_ISDIR(statbuf.st_mode)) {
                printf("📁 [%s]\n", entry->d_name);
                list_dir(path, level + 1);
            } else {
                printf("📄 %s\n", entry->d_name);
            }
        }
    }
    closedir(dir);
}
int main() {
    printf("Поточний каталог:\n");
    printf("📁 [.]\n");
    list_dir(".", 1);
    return 0;
}
