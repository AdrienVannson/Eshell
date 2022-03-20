#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "cpp.h"
#include "env.h"
#include "processes.h"

#define TOKEN_SEPARATORS " \n\t"

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

void run_in_foreground(const int pid)
{
    set_foreground_process(pid);

    // Wait until the process terminates
    while (waitpid(pid, NULL, 0) == -1) {}

    set_foreground_process(-1);
}

int main()
{
    // Set the defaut value of the PATH
    set_value_to_env("PATH",
        "/usr/local/sbin:"
        "/usr/local/bin:"
        "/usr/sbin:"
        "/usr/bin:"
        "/sbin:"
        "/bin:"
        "/usr/games:"
        "/usr/local/games:"
        "/snap/bin"
    );

    printf("Welcome in ÉShell!\n");

    // Connect signals
    struct sigaction sa;
    sa.sa_handler = signal_received;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);

    bool is_over = false;

    while (!is_over) {
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

        char* command_name = strtok(command, TOKEN_SEPARATORS);

        if (command_name == NULL) { // Empty line
        } else if (!strcmp(command_name, "exit")) { // Exit
            is_over = true;
        } else if (!strcmp(command_name, "env")) {
            print_env();
        } else if (!strcmp(command_name, "export")) { // Set a variable
            char* var_name = strtok(NULL, " =");
            char* value = strtok(NULL, "\n");
            set_value_to_env(var_name, value);
        } else if (!strcmp(command_name, "echo")) { // Show a variable
            char* var_name = strtok(NULL, TOKEN_SEPARATORS);

            if (var_name[0] != '$') {
                printf("The name of the variable must start with a dollar\n");
            } else {
                char *val = get_value_from_env(var_name + 1);
                if (val == NULL) {
                    printf("Unknown variable\n");
                } else {
                    printf("%s\n", val);
                }
            }
        } else { // Execute a command
            char* path = strdup(get_value_from_env("PATH"));
            char* file = NULL;

            if (access(command_name, F_OK) == 0) {
                file = strdup(command_name);
            } else {
                char* folder = strtok(path, ":");
                while (folder) {
                    char* current_file = malloc((strlen(folder) + strlen(command_name) + 2) * sizeof(char));
                    strcpy(current_file, folder);
                    current_file[strlen(folder)] = '/';
                    strcpy(current_file + strlen(folder) + 1, command_name);

                    if (access(current_file, F_OK) == 0) {
                        file = strdup(current_file);
                        break;
                    }

                    free(current_file);
                    folder = strtok(NULL, ":");
                }
            }

            free(path);

            if (file == NULL) {
                printf("Command not found\n");
            } else {
                const int pid = fork();

                if (pid == 0) { // Child process
                    // The syscalls are sent to all the processes in the same process
                    // group. Since we do not want the signals sent to the EShell to
                    // be also sent to the other processes, we move the other processes
                    // to a new group.
                    setpgid(0, 0);

                    execl(file, file, (char*)NULL);
                    printf("Error: can't execute %s\n", file);
                    exit(0);
                } else {
                    run_in_foreground(pid);
                }

                free(file);
            }
        }

        free(command);
    }

    free_env();
}
