#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *rwho_f = popen("rwho --all", "r");
	if (rwho_f == NULL) {
        	perror("Помилка виконання rwho");
        	return 1;
    	}
	pclose(rwho_f);

	FILE *more_f =  popen("more -e","r");
	if (more_f == NULL) {
        	perror("Помилка виконання more");
        	return 1;
    	}
	pclose(more_f);
	return 0;
}
