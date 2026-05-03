#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

static int myCompare(const void* a, const void* b) {
	return strcmp(*(const char**)a, *(const char**)b);
}

void list_subdirs(const char *base_path, int level) {
	DIR *dir;
	struct dirent *entry;
	struct stat statbuf;
	char path[1024];

	if ((dir = opendir(base_path)) == NULL) {
		return;
	}

	char *arr[1024]; int n = 0;

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}

		snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

		if (stat(path, &statbuf) == 0) {
			if (S_ISDIR(statbuf.st_mode)) {
				arr[n] = strdup(entry->d_name); n++;
			}
		}
	}
	closedir(dir);

	qsort(arr, n, sizeof(const char*), myCompare);

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < level; i++) {
			printf(" ");
		}

		printf("📁 [%s]\n", arr[j]);

		snprintf(path, sizeof(path), "%s/%s", base_path, arr[j]);
		list_subdirs(path, level + 1);

		free(arr[j]);
	}
}

int main() {
	printf("Поточний каталог:\n");
	printf("📁 [.]\n");

	list_subdirs(".", 1);

	return 0;
}
