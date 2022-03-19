#ifndef PROCESSES_H
#define PROCESSES_H

// Set the PID of the process running in the foreground
void set_foreground_process(const int pid);

// Kill the process running in the foreground
void kill_process();

// Suspend the process running in the foreground
void suspend_process();

#endif // PROCESSES_H
