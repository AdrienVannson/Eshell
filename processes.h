#ifndef PROCESSES_H
#define PROCESSES_H

// Add a process to the process list
void add_process(const int pid, const char* command);

// Send a signal to a process, and update the status of the process
void send_signal(const int pid, const int signal);

// Set the PID of the process running in the foreground
void set_foreground_process(const int pid);

// Kill the process running in the foreground
void kill_foreground_process();

// Suspend the process running in the foreground
void suspend_foreground_process();

// Show the list of the processes created by ÉShell
void print_process_list();

// Kill all the processes and free the memory
void kill_all_processes();

#endif // PROCESSES_H
