#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSES 100
#define MAX_NAME_LEN 32

// Process structure
typedef struct {
    int pid;              // Process ID
    char name[MAX_NAME_LEN];  // Process name
    int arrival_time;     // Time when process arrives
    int burst_time;       // CPU time needed
    int remaining_time;   // Remaining CPU time
    int priority;         // Priority level (lower number = higher priority)
    int start_time;       // Time when process first starts
    int finish_time;      // Time when process finishes
    int waiting_time;     // Time spent waiting
    int turnaround_time;  // Total time from arrival to completion
} Process;

// Queue structure for FIFO scheduling
typedef struct {
    Process* processes[MAX_PROCESSES];
    int front;
    int rear;
    int count;
} Queue;

// Function prototypes
void fifo_scheduling(Process processes[], int n);
void sjf_scheduling(Process processes[], int n);
void priority_scheduling(Process processes[], int n);
void round_robin_scheduling(Process processes[], int n, int quantum);
void print_results(Process processes[], int n, const char* algorithm);
void print_gantt_chart(Process processes[], int n);
void reset_processes(Process processes[], int n);
void generate_sample_processes(Process processes[], int n);
void print_menu();

int main() {
    Process processes[MAX_PROCESSES];
    int n = 5;  // Number of processes
    int choice, quantum;
    
    printf("Process Scheduler Simulator\n");
    printf("Simulates FIFO, SJF, Priority, and Round Robin scheduling algorithms\n\n");
    
    // Generate sample processes
    generate_sample_processes(processes, n);
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        // Reset processes for each simulation
        reset_processes(processes, n);
        
        switch (choice) {
            case 1:  // FIFO
                printf("\n=== First-In-First-Out (FIFO) Scheduling ===\n");
                fifo_scheduling(processes, n);
                print_results(processes, n, "FIFO");
                break;
                
            case 2:  // SJF
                printf("\n=== Shortest Job First (SJF) Scheduling ===\n");
                sjf_scheduling(processes, n);
                print_results(processes, n, "SJF");
                break;
                
            case 3:  // Priority
                printf("\n=== Priority Scheduling ===\n");
                priority_scheduling(processes, n);
                print_results(processes, n, "Priority");
                break;
                
            case 4:  // Round Robin
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                printf("\n=== Round Robin Scheduling (Quantum = %d) ===\n", quantum);
                round_robin_scheduling(processes, n, quantum);
                print_results(processes, n, "Round Robin");
                break;
                
            case 5:  // Exit
                printf("Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();  // Wait for user input
    }
    
    return 0;
}

// FIFO (First-In-First-Out) Scheduling
void fifo_scheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    
    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    while (completed < n) {
        int selected = -1;
        
        // Find the first process that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                selected = i;
                break;
            }
        }
        
        if (selected == -1) {
            current_time++;  // No process available, advance time
            continue;
        }
        
        // Execute the process
        Process* p = &processes[selected];
        if (p->start_time == -1) {
            p->start_time = current_time;
        }
        
        current_time += p->remaining_time;
        p->finish_time = current_time;
        p->remaining_time = 0;
        p->waiting_time = p->start_time - p->arrival_time;
        p->turnaround_time = p->finish_time - p->arrival_time;
        completed++;
    }
}

// SJF (Shortest Job First) Scheduling
void sjf_scheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        int selected = -1;
        int min_burst = 999999;
        
        // Find the process with shortest remaining time among arrived processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_burst) {
                    min_burst = processes[i].remaining_time;
                    selected = i;
                }
            }
        }
        
        if (selected == -1) {
            current_time++;  // No process available, advance time
            continue;
        }
        
        // Execute the process
        Process* p = &processes[selected];
        if (p->start_time == -1) {
            p->start_time = current_time;
        }
        
        current_time += p->remaining_time;
        p->finish_time = current_time;
        p->remaining_time = 0;
        p->waiting_time = p->start_time - p->arrival_time;
        p->turnaround_time = p->finish_time - p->arrival_time;
        completed++;
    }
}

// Priority Scheduling
void priority_scheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        int selected = -1;
        int highest_priority = 999999;
        
        // Find the process with highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected = i;
                }
            }
        }
        
        if (selected == -1) {
            current_time++;  // No process available, advance time
            continue;
        }
        
        // Execute the process
        Process* p = &processes[selected];
        if (p->start_time == -1) {
            p->start_time = current_time;
        }
        
        current_time += p->remaining_time;
        p->finish_time = current_time;
        p->remaining_time = 0;
        p->waiting_time = p->start_time - p->arrival_time;
        p->turnaround_time = p->finish_time - p->arrival_time;
        completed++;
    }
}

// Round Robin Scheduling
void round_robin_scheduling(Process processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;
    
    // Queue for round robin
    Queue queue;
    queue.front = 0;
    queue.rear = -1;
    queue.count = 0;
    
    int* in_queue = (int*)calloc(n, sizeof(int));
    
    while (completed < n) {
        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                processes[i].remaining_time > 0 && 
                !in_queue[i]) {
                queue.rear = (queue.rear + 1) % MAX_PROCESSES;
                queue.processes[queue.rear] = &processes[i];
                queue.count++;
                in_queue[i] = 1;
            }
        }
        
        if (queue.count == 0) {
            current_time++;  // No process available, advance time
            continue;
        }
        
        // Execute the front process
        Process* p = queue.processes[queue.front];
        queue.front = (queue.front + 1) % MAX_PROCESSES;
        queue.count--;
        in_queue[p - processes] = 0;  // Mark as not in queue
        
        if (p->start_time == -1) {
            p->start_time = current_time;
        }
        
        int exec_time = (p->remaining_time < quantum) ? p->remaining_time : quantum;
        current_time += exec_time;
        p->remaining_time -= exec_time;
        
        if (p->remaining_time == 0) {
            p->finish_time = current_time;
            p->waiting_time = p->finish_time - p->arrival_time - p->burst_time;
            p->turnaround_time = p->finish_time - p->arrival_time;
            completed++;
        } else {
            // Put process back in queue
            queue.rear = (queue.rear + 1) % MAX_PROCESSES;
            queue.processes[queue.rear] = p;
            queue.count++;
            in_queue[p - processes] = 1;
        }
    }
    
    free(in_queue);
}

// Print scheduling results
void print_results(Process processes[], int n, const char* algorithm) {
    printf("\n%-5s %-10s %-8s %-8s %-8s %-8s %-10s %-12s\n", 
           "PID", "Name", "Arrival", "Burst", "Waiting", "Turnaround", "Start", "Finish");
    printf("------------------------------------------------------------------------\n");
    
    float avg_waiting = 0, avg_turnaround = 0;
    
    for (int i = 0; i < n; i++) {
        printf("%-5d %-10s %-8d %-8d %-8d %-8d %-10d %-12d\n",
               processes[i].pid,
               processes[i].name,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].start_time,
               processes[i].finish_time);
        
        avg_waiting += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", avg_waiting / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);
}

// Print Gantt chart
void print_gantt_chart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");
    
    printf("0");
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += processes[i].burst_time;
        printf("    %d", time);
    }
    printf("\n");
}

// Reset processes for new simulation
void reset_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].finish_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
}

// Generate sample processes
void generate_sample_processes(Process processes[], int n) {
    // Sample process data
    Process sample[] = {
        {1, "TextEdit", 0, 8, 8, 3, -1, 0, 0, 0},
        {2, "Compiler", 1, 4, 4, 1, -1, 0, 0, 0},
        {3, "Browser", 2, 9, 9, 4, -1, 0, 0, 0},
        {4, "Database", 3, 5, 5, 2, -1, 0, 0, 0},
        {5, "Antivirus", 4, 2, 2, 5, -1, 0, 0, 0}
    };
    
    for (int i = 0; i < n; i++) {
        processes[i] = sample[i];
    }
}

// Print menu
void print_menu() {
    printf("\n===== Process Scheduler Simulator =====\n");
    printf("1. First-In-First-Out (FIFO)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("3. Priority Scheduling\n");
    printf("4. Round Robin Scheduling\n");
    printf("5. Exit\n");
    printf("====================================\n");
}