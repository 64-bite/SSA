#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

int main() {
    struct rlimit rl;

    rl.rlim_cur = 100; 
    rl.rlim_max = 1024;
    setrlimit(RLIMIT_FSIZE, &rl);


    FILE *f = fopen("dice.txt", "w");
    if (f == NULL) return 1;

    srand(time(NULL));
    printf("Запис у файл почався...\n");


    while (1) {
        int dice = (rand() % 6) + 1;
        if (fprintf(f, "Результат: %d\n", dice) < 0) {
            printf("\n[!] Стоп! Досягнуто ліміт розміру файлу.\n");
            break;
        }
        fflush(f);
        printf("%d ", dice);
    }

    fclose(f);
    return 0;
}
