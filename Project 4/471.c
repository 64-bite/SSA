#include <stdio.h>
#include <stdlib.h>
struct sbar {
        int id;
        char name[10];
};

int main(){
        struct sbar *ptr, *newptr;

        ptr = calloc(1000, sizeof(struct sbar));
        printf("ptr memory space is located: %p\n", (void*)ptr);

        newptr = realloc(ptr, 500*sizeof(struct sbar));
        printf("newptr memory space is located: %p\n", (void*)newptr);

        ptr = newptr;
        free(ptr);
        return 0;
}



