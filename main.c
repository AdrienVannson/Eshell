#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cpp.h"

void kill_process()
{
    printf("KILL\n");
}

void suspend_process()
{
    printf("SUSPEND\n");
}

int main()
{
    printf("Welcome in ÉShell!\n");

    // Connect signals
    signal(SIGTSTP, suspend_process);
    signal(SIGINT, kill_process);

    while (true) {
        // Show a ladder (ÉShell) on the left of the screen
        printf("╬═╬ ");
        char command[1024];
        scanf("%s", command);

        if (!strcmp(command, "exit")) {
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
    }
}
