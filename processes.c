#include <stdio.h>
#include <signal.h>

#include "processes.h"

// PID of the process running in the foreground,
// or -1 if no process is running
int pid_foreground = -1;

void set_foreground_process(const int pid)
{
    pid_foreground = pid;
}

void kill_process()
{
    if (pid_foreground != -1) {
        kill(pid_foreground, SIGINT);
        printf("Killed\n");
    }
}

void suspend_process()
{
    printf("SUSPEND\n");
}
