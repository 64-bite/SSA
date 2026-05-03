#include <stdio.h>
#include <stdlib.h>

void process_file(FILE *file, const char *filename) {
    char line[1024];
    int line_count = 0;
    FILE *tty = fopen("/dev/tty", "r");
    if (tty == NULL) {
        perror("Error: failed to open /dev/tty");
        return;
    }

    printf("--- Reading file: %s ---\n", filename);

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        line_count++;

        if (line_count == 20) {
            printf("\033[7m--More (Press Enter)--\033[m");
            int c;
            while ((c = fgetc(tty)) != '\n' && c != EOF) {
            }
            line_count = 0;
        }
    }
    fclose(tty);
    printf("\n--- End of file: %s ---\n\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Error: failed to open file %s\n", argv[i]);
            continue;
        }

        process_file(file, argv[i]);
        fclose(file);
    }

    return 0;
}
