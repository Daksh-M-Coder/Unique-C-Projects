# Process Scheduler Simulator - Code Explanation

## Program Structure
The process scheduler simulator implements four fundamental CPU scheduling algorithms to demonstrate how different policies affect system performance. It uses data structures to represent processes and implements scheduling logic for FIFO, SJF, Priority, and Round Robin algorithms. The program calculates and displays performance metrics for comparison.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
```
- `stdio.h`: For input/output operations
- `stdlib.h`: For standard library functions and memory allocation
- `string.h`: For string manipulation functions
- `time.h`: For time-related functions (not heavily used in this implementation)

### Constants
```c
#define MAX_PROCESSES 100
#define MAX_NAME_LEN 32
```
- Maximum number of processes and name length for memory management

### Data Structures

#### Process Structure
```c
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
```
- Represents a process with all relevant attributes
- Tracks both static properties (PID, name, burst time) and dynamic properties (timing metrics)

#### Queue Structure
```c
typedef struct {
    Process* processes[MAX_PROCESSES];
    int front;
    int rear;
    int count;
} Queue;
```
- Circular queue implementation for Round Robin scheduling
- Stores pointers to processes rather than copying data

## Detailed Code Walkthrough

### Main Function
```c
int main() {
    Process processes[MAX_PROCESSES];
    int n = 5;  // Number of processes
    int choice, quantum;
    
    printf("Process Scheduler Simulator\n");
    // ... introductory messages ...
    
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
                fifo_scheduling(processes, n);
                print_results(processes, n, "FIFO");
                break;
            // ... other cases ...
            case 5:  // Exit
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
```
- Initializes sample processes and provides interactive interface
- Resets process state between simulations
- Handles user input and algorithm selection

### FIFO (First-In-First-Out) Scheduling
```c
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
```
- Sorts processes by arrival time for proper FIFO order
- Executes processes in sequence without preemption
- Updates timing metrics for each completed process

### SJF (Shortest Job First) Scheduling
```c
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
```
- Selects process with shortest remaining time at each decision point
- Non-preemptive implementation (runs processes to completion)
- Minimizes average waiting time but can cause starvation

### Priority Scheduling
```c
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
```
- Selects process with highest priority (lowest numerical value)
- Similar non-preemptive approach to SJF
- Can suffer from priority inversion and starvation issues

### Round Robin Scheduling
```c
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
```
- Implements preemptive scheduling with time quantum
- Uses circular queue to manage process execution order
- Processes are suspended and requeued if not completed within quantum
- More complex but provides fair CPU sharing

### Performance Metrics Calculation
```c
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
```
- Calculates and displays key performance metrics
- Shows individual process statistics and averages
- Enables comparison between scheduling algorithms

### Helper Functions

#### Process Management
```c
void reset_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].finish_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
}
```
- Resets process state between simulations
- Preserves static properties while clearing timing data

#### Sample Data Generation
```c
void generate_sample_processes(Process processes[], int n) {
    // Sample process data
    Process sample[] = {
        {1, "TextEdit", 0, 8, 8, 3, -1, 0, 0, 0},
        {2, "Compiler", 1, 4, 4, 1, -1, 0, 0, 0},
        // ... additional processes ...
    };
    
    for (int i = 0; i < n; i++) {
        processes[i] = sample[i];
    }
}
```
- Provides realistic sample data for demonstrations
- Includes varied arrival times, burst times, and priorities

## Program Flow
1. Initialize sample processes with realistic attributes
2. Present menu for algorithm selection
3. Reset process state for clean simulation
4. Execute selected scheduling algorithm
5. Calculate and display performance metrics
6. Wait for user input before next iteration
7. Continue until user exits

## Learning Points
1. **Scheduling Algorithms**: Implementation of fundamental OS scheduling policies
2. **Performance Metrics**: Waiting time and turnaround time calculations
3. **Data Structures**: Queue implementation for Round Robin
4. **Algorithm Comparison**: Observing trade-offs between algorithms
5. **Process Lifecycle**: Managing process states and transitions
6. **Preemptive vs Non-preemptive**: Understanding scheduling characteristics

## Limitations and Possible Improvements
1. **Static Sample Data**: Fixed process set rather than dynamic generation
2. **No Gantt Chart**: Visual timeline representation missing
3. **Limited Metrics**: Only basic performance metrics calculated
4. **No Real-Time Simulation**: Instantaneous execution rather than time-based
5. **No Context Switching Overhead**: Simplified model without switching costs
6. **No Aging Mechanism**: Priority scheduling doesn't address starvation