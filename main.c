#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cpp.h"
#include "processes.h"

int main()
{
    printf("Welcome in ÉShell!\n");

    // Connect signals
    signal(SIGTSTP, suspend_process);
    signal(SIGINT, kill_process);

    while (true) {
        // Show a ladder (ÉShell) on the left of the screen
        printf("╬═╬ ");

        // Read and parse a command
        char* command = NULL;
        size_t command_length = 0;
        getline(&command, &command_length, stdin);

        char* command_name = strtok(command, " \t\n");

        if (command_name == NULL) { // Empty line
            continue;
        } else if (!strcmp(command_name, "exit")) { // Exit
            return 0;
        } else { // Execute a command
            const int pid = fork();

            if (pid == 0) { // Child process
                char *filename = command;

                execl(filename, filename, (char*)NULL);
                printf("Error: can't execute %s\n", filename);
                return 0;
            } else {
                printf("Child created: %d\n", pid);
            }
        }

        free(command);
    }
}
