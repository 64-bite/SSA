#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define MIN_UID 1000

int main() {
    	uid_t current_uid = getuid();
    	struct passwd *pw = getpwuid(current_uid);
    	char current_user[256] = {0};

    	if (pw != NULL) {
        	strncpy(current_user, pw->pw_name, sizeof(current_user) - 1);
    	} else {
        	perror("Не вдалося отримати дані поточного користувача");
        	return 1;
    	}

    	printf("Аналіз облікових записів (мова C)...\n");
    	printf("Поточний користувач: %s (UID: %d)\n", current_user, current_uid);
    	printf("Шукаємо інших користувачів з UID >= %d...\n", MIN_UID);
    	printf("------------------------------------------------\n");

    	FILE *fp = popen("getent passwd", "r");
    	if (fp == NULL) {
        	perror("Помилка під час виклику popen");
        	return 1;
    	}

    	char line[1024];
    	int count = 0;

    	while (fgets(line, sizeof(line), fp) != NULL) {
        	char *username = strtok(line, ":");
        	char *password = strtok(NULL, ":");
        	char *uid_str = strtok(NULL, ":");

        	if (username != NULL && uid_str != NULL) {
            		int uid = atoi(uid_str);
            		if (uid >= MIN_UID && uid != 65534 && strcmp(username, current_user) != 0) {
                		printf("- %s (UID: %d)\n", username, uid);
                		count++;
			}
		}
	}

	pclose(fp);

	printf("------------------------------------------------\n");
	if (count == 0) {
		printf("Інших звичайних користувачів на цій системі не знайдено.\n");
	} else {
		printf("Усього знайдено інших звичайних користувачів: %d\n", count);
	}
	return 0;
}
