#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define MAX_HISTORY 100

char history[MAX_HISTORY][BUFFER_SIZE];
int history_count = 0;

void execute_command(char* command, int background) {
    char* token = strtok(command, " ");
    char* args[BUFFER_SIZE];
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    if (i == 0) {
        return;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else {
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

void add_to_history(char* command) {
    if (history_count >= MAX_HISTORY) {
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            strcpy(history[i], history[i + 1]);
        }
        history_count--;
    }
    strcpy(history[history_count], command);
    history_count++;
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}

int main(void) {
    char command[BUFFER_SIZE];
    while (1) {
        fprintf(stdout, "my-shell> ");
        memset(command, 0, BUFFER_SIZE);
        fgets(command, BUFFER_SIZE, stdin);

        if (command[0] == '\n') {
            continue;
        }
        command[strcspn(command, "\n")] = '\0';
        int background = 0;
        if (command[strlen(command) - 1] == '&') {
            background = 1;
            command[strlen(command) - 1] = '\0';
        }
        if (strncmp(command, "exit", 4) == 0) {
            break;
        }
        else if (strncmp(command, "history", 7) == 0) {
            print_history();
        }
        else {
            add_to_history(command);
            execute_command(command, background);
        }
    }

    return 0;
}
