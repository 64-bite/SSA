#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- Перевірка імені користувача (whoami) ---\n");
    if (system("whoami") == -1) {
        perror("Помилка виконання whoami");
        return 1;
    }

    printf("\n--- Перевірка ідентифікаторів та груп (id) ---\n");
    if (system("id") == -1) {
        perror("Помилка виконання id");
        return 1;
    }

    return 0;
}
