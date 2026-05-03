#include <stdio.h>
#include <regex.h>

int main() {
        FILE *cat = fopen("cat.txt", "r");
        char line[1024];
        regex_t regex;

        if (cat == NULL) {
                return 1;
        }

        regcomp(&regex, "cought", REG_EXTENDED | REG_NEWLINE);

        while (fgets(line, sizeof(line), cat) != NULL) {
                if (regexec(&regex, line, 0, NULL, 0) == 0) {
                        printf("%s", line);
                }
        }
        regfree(&regex);
        fclose(cat);
        return 0;
}
