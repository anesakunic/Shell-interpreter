#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

int main(int argc, char *argv[], char *envp[]) {
    char c = '\0';
    char input[MAX_INPUT_LENGTH] = {0};
    int inputIndex = 0;

    while (1) {
        printf("\n[MY_SHELL] Enter a command: ");

        // Read input character by character
        while ((c = getchar()) != '\n' && c != EOF) {
            input[inputIndex] = c;
            inputIndex++;

            // Check for buffer overflow
            if (inputIndex >= MAX_INPUT_LENGTH) {
                fprintf(stderr, "Error: Input too long. Maximum length is %d characters.\n", MAX_INPUT_LENGTH);
                return 1;
            }
        }

        // Null-terminate the input string
        input[inputIndex] = '\0';

        // If the input is not empty
        if (strlen(input) > 0) {
            // Create a child process to execute the command
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                // This is the child process
                // Use execvp() to execute the command
                char *arguments[MAX_INPUT_LENGTH] = {0};
                arguments[0] = strtok(input, " ");
                int i = 1;
                while (arguments[i - 1] != NULL) {
                    arguments[i] = strtok(NULL, " ");
                    i++;
                }
                arguments[i] = NULL;

                // Check for supported commands
                if (strcmp(arguments[0], "ls") == 0 || strcmp(arguments[0], "pwd") == 0 || strcmp(arguments[0], "grep") == 0) {
                    execvp(arguments[0], arguments);
                } else if (strcmp(arguments[0], "cd") == 0) {
                    if (arguments[1] != NULL) {
                        if (chdir(arguments[1]) == -1) {
                            perror("chdir");
                        }
                    } else {
                        fprintf(stderr, "cd: missing argument\n");
                    }
                } else {
                    fprintf(stderr, "Command not supported: %s\n", arguments[0]);
                    exit(EXIT_FAILURE);
                }
            } else {
                // This is the parent process
                // Wait for the child process to finish
                wait(NULL);
            }

            // Reset the input buffer for the next command
            memset(input, 0, MAX_INPUT_LENGTH);
            inputIndex = 0;
        }
    }

    printf("\n");
    return 0;
}
