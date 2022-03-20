#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "cpp.h"
#include "processes.h"

#define MAX_PROCESS_COUNT 1000

// The processes in the list may no longer exist
typedef struct {
    int pid;
    bool is_suspended;
    char* command; // Command used to create the process
} Process;

Process processes[MAX_PROCESS_COUNT];

int next_process = 0; // Where to place a new process in the array

// PID of the process running in the foreground,
// or -1 if no process is running
int pid_foreground = -1;

// Delete the processes that no longer exists
void update_process_states()
{
    for (int i = 0; i < next_process; i++) {
        if (processes[i].pid != 0) {
            int result;
            do {
                result = waitpid(processes[i].pid, NULL, WNOHANG);
            } while (result > 0);

            if (result == -1) { // The process no longer exists
                processes[i].pid = 0;
                free(processes[i].command);
            }
        }
    }
}

// Add a process to the process list
void add_process(const int pid, const char* command)
{
    processes[next_process].pid = pid;
    processes[next_process].is_suspended = false;
    processes[next_process].command = strdup(command);
    next_process++;
}

// Send a signal to a process, and update the status of the process
void send_signal(const int pid, const int signal)
{
    for (int i = 0; i < next_process; i++) {
        if (processes[i].pid == pid) {
            kill(pid, signal);

            switch(signal) {
            case SIGTSTP:
                processes[i].is_suspended = true;

                // Move the process to the end of the array
                memcpy(processes + next_process, processes + i, sizeof(Process));
                memset(processes + i, 0, sizeof(Process));
                next_process++;

                break;

            case SIGCONT:
                processes[i].is_suspended = false;
                break;
            }

            return;
        }
    }
}

// Wait until the process terminates
void run_in_foreground(const int pid)
{
    pid_foreground = pid;
    while (waitpid(pid, NULL, WUNTRACED) == -1) {}
    pid_foreground = -1;
}

// Kill the process running in the foreground
void kill_foreground_process()
{
    if (pid_foreground != -1) {
        send_signal(pid_foreground, SIGINT);
    }
}

// Suspend the process running in the foreground
void suspend_foreground_process()
{
    if (pid_foreground != -1) {
        send_signal(pid_foreground, SIGTSTP);
    }
}

// Show the list of the processes created by ÉShell
void print_process_list()
{
    update_process_states();

    for (int i = 0; i < next_process; i++) {
        if (processes[i].pid != 0) {
            printf("State: %s, ", processes[i].is_suspended ? "Suspended" : "Running");
            printf("PID: %d, Command: %s\n", processes[i].pid, processes[i].command);
        }
    }
}

// Kill all the processes and free the memory
void kill_all_processes()
{
    for (int i = 0; i < next_process; i++) {
        if (processes[i].pid != 0) {
            kill(processes[i].pid, SIGINT);
            free(processes[i].command);
            processes[i].pid = 0;
        }
    }
}
;
