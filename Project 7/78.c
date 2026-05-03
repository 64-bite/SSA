#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list_dir(const char *base_path) {
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
            if (S_ISDIR(statbuf.st_mode)) {
                continue;
            } else {
		char chr[5];
                printf("📄 %s\n", entry->d_name);
		printf("What would you like to do with this file?\n");
		printf("----------------------------------\n");
		printf("1. Delete this file\n");
		printf("2. Continue\n");
		fflush(stdout);
		if(fgets(chr, sizeof(chr), stdin) != NULL){
			if(chr[0] == '1'){
				if(remove(path) == 0) {
					printf("File was deleted!\n");
				} else {
					perror("Error: file wasn't deleted!\n");
				}
			}
		}
            }
        }
    }
    closedir(dir);
}
int main() {
    printf("Program start!");
    list_dir(".");
    return 0;
}
