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
        	if (S_ISDIR(statbuf.st_mode)) {
                	list_dir(path, level + 1);
            	} else {
                	size_t len = strlen(entry->d_name);
			if (len >= 2 && strcmp(entry->d_name + len - 2, ".c") == 0) {
                    	printf("Знайдено C-файл: 📄 %s. Надати іншим дозвіл на читання? (y/n): ", path);
                    	fflush(stdout);
                    	char chr[10];
                    	if (fgets(chr, sizeof(chr), stdin) != NULL) {
                        	if (chr[0] == 'y' || chr[0] == 'Y') {
					if (chmod(path, statbuf.st_mode | S_IROTH) == 0) {
						printf("Success!\n");
                            		} else {
                                		perror("Error!\n");
                            		}
         			} else {
                                	printf("Search.\n");
                     		}
                    	}
                }
            }
        }
    }
    closedir(dir);
}

int main() {
    printf("Search of .c files\n");
    printf("------------------------------------------------------\n");

    list_dir(".", 0);

    printf("------------------------------------------------------\n");
    printf("Ready!\n");
    return 0;
}
