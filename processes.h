#ifndef PROCESSES_H
#define PROCESSES_H

// Add a process to the process list
void add_process(const int pid, const char* command);

// Send a signal to a process, and update the status of the process
void send_signal(const int pid, const int signal);

// Wait until the process terminates
void run_in_foreground(const int pid);

// Kill the process running in the foreground
void kill_foreground_process();

// Suspend the process running in the foreground
void suspend_foreground_process();

// Restart the last process stopped
void restart_last_stop();

// Show the list of the processes created by ÉShell
void print_process_list();

// Kill all the processes and free the memory
void kill_all_processes();

#endif // PROCESSES_H
