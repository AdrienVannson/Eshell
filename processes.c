#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "cpp.h"
#include "processes.h"

#define MAX_PROCESS_COUNT 1000

struct {
    int pid;
    bool is_suspended;
    char* command; // Command used to create the process
} processes[MAX_PROCESS_COUNT];

// PID of the process running in the foreground,
// or -1 if no process is running
int pid_foreground = -1;

// Add a process to the process list
void add_process(const int pid, const char* command)
{
    for (int i = 0; i < MAX_PROCESS_COUNT; i++) {
        if (processes[i].pid == 0) {
            processes[i].pid = pid;
            processes[i].is_suspended = false;
            processes[i].command = strdup(command);
            return;
        }
    }
}

// Set the PID of the process running in the foreground
void set_foreground_process(const int pid)
{
    pid_foreground = pid;
}

// Kill the process running in the foreground
void kill_foreground_process()
{
    if (pid_foreground != -1) {
        kill(pid_foreground, SIGINT);
        printf("Killed\n");
    }
}

// Suspend the process running in the foreground
void suspend_foreground_process()
{
    if (pid_foreground != -1) {
        kill(pid_foreground, SIGTSTP);
        printf("Suspended\n");
    }
}

// Show the list of the processes created by ÉShell
void print_process_list()
{
    for (int i = 0; i < MAX_PROCESS_COUNT; i++) {
        if (processes[i].pid != 0) {
            printf("State: %s, ", processes[i].is_suspended ? "Suspended" : "Running");
            printf("PID: %d, Command: %s\n", processes[i].pid, processes[i].command);
        }
    }
}

// Kill all the processes and free the memory
void kill_all_processes()
{
    for (int i = 0; i < MAX_PROCESS_COUNT; i++) {
        if (processes[i].pid != 0) {
            kill(processes[i].pid, SIGINT);
            free(processes[i].command);
        }
    }
}
