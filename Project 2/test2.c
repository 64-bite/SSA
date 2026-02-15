#include <stdio.h>

void stack(int level) {
    double large[1024];
    int another[2048];
    printf("Level %d: Stack pointer is near %p\n", level, (void*)&large);
    if (level < 3) {
        stack(level + 1);
    }
}
int main() {
    int main_var;
    printf("Main stack top:        %p\n", (void*)&main_var);
    printf("--- Growing the stack ---\n");
    stack(1);
    return 0;
}
