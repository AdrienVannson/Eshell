#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "cpp.h"
#include "processes.h"

void signal_received(const int signal)
{
    switch (signal) {
    case SIGINT:
        kill_process();
        break;

    case SIGTSTP:
        suspend_process();
        break;
    }
}

int main()
{
    printf("Welcome in ÉShell!\n");

    // Connect signals
    struct sigaction sa;
    sa.sa_handler = signal_received;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);

    while (true) {
        // Show a ladder (ÉShell) on the left of the screen
        printf("╬═╬ ");

        // Read and parse a command
        char* command = NULL;
        size_t command_length = 0;

        // A syscall occured during the getline
        if (getline(&command, &command_length, stdin) == -1) {
            clearerr(stdin);
            continue;
        }

        char* command_name = strtok(command, " \t\n");

        if (command_name == NULL) { // Empty line
        } else if (!strcmp(command_name, "exit")) { // Exit
            return 0;
        } else { // Execute a command
            const int pid = fork();

            if (pid == 0) { // Child process
                // The syscalls are sent to all the processes in the same process
                // group. Since we do not want the signals sent to the EShell to
                // be also sent to the other processes, we move the other processes
                // to a new group.
                setpgid(0, 0);

                execl(command_name, command_name, (char*)NULL);
                printf("Error: can't execute %s\n", command_name);
                return 0;
            } else {
                set_foreground_process(pid);
                waitpid(pid, NULL, 0);
                set_foreground_process(-1);
            }
        }

        free(command);
    }
}
