#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

void setup_signals() {
    signal(SIGINT, SIG_IGN);
}

void execute_single_command(char *cmd) {
    char *args[MAX_ARGS];
    int i = 0;
    int fd_in = -1, fd_out = -1;

    char *token = strtok(cmd, " \t\n");
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) fd_in = open(token, O_RDONLY);
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) fd_out = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) fd_out = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    if (args[0] == NULL) exit(0);

    if (fd_in != -1) {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (fd_out != -1) {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }

    signal(SIGINT, SIG_DFL);

    if (execvp(args[0], args) < 0) {
        perror("Помилка exec");
        exit(EXIT_FAILURE);
    }
}
void pipeline(char *line) {
	char *commands[MAX_ARGS];
	int num_cmds = 0;
	char *ptr;

	char *cmd = strtok_r(line, "|", &ptr);
	while(cmd != NULL){
		commands[num_cmds++] = cmd;
		cmd = strtok_r(NULL, "|", &ptr);
	}

	int in_fd = 0;
	int fd[2];

	for(int i = 0; i< num_cmds; i++){
		if(pipe(fd) < 0){
			perror("Error in pipe!");
			return;
		}
		pid_t pid = fork();
		if(pid == 0){
			if(in_fd != 0){
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}

			if(i != num_cmds -1){
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			close(fd[1]);
			execute_single_command(commands[i]);
		} else if(pid < 0) {
			perror("Error in fork()!");
			return;
		}
		if(in_fd != 0) close(in_fd);
		close(fd[1]);
		in_fd = fd[0];
	}
	if(in_fd != 0) close(in_fd);
	for(int i = 0; i < num_cmds; i++){
		wait(NULL);
	}
}
int main(){
char line[MAX_CMD_LEN];
    setup_signals();

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) continue;
        if (strcmp(line, "exit") == 0) break;

        pipeline(line);
    }

    return 0;
}
