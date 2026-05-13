#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void receiver_handler(int signo, siginfo_t *info, void *context) {
    if (signo == SIGUSR1) {
        printf("Одержувач (PID: %d): Отримано повідомлення: %d\n", getpid(), info->si_value.sival_int);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = receiver_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Помилка sigaction");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Помилка fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        for (int i = 0; i < 5; i++) {
            pause();
        }
        exit(EXIT_SUCCESS);
    }
    else {
        union sigval value;
        int messages[] = {104, 256, 512, 1024, 2048};
        int num_messages = sizeof(messages) / sizeof(messages[0]);

        for (int i = 0; i < num_messages; i++) {
            sleep(1);
            value.sival_int = messages[i];

            printf("Відправник (PID: %d): Відправка повідомлення: %d\n", getpid(), value.sival_int);

            if (sigqueue(pid, SIGUSR1, value) == -1) {
                perror("Помилка sigqueue");
            }
        }

        wait(NULL);
    }

    return 0;
}
