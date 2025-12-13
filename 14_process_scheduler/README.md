# Process Scheduler Simulator

## Description
A process scheduler simulator that demonstrates four fundamental CPU scheduling algorithms: First-In-First-Out (FIFO), Shortest Job First (SJF), Priority Scheduling, and Round Robin. The simulator shows how different scheduling policies affect process waiting times and system efficiency.

## Features
- Simulation of four scheduling algorithms:
  - FIFO (First-In-First-Out)
  - SJF (Shortest Job First)
  - Priority Scheduling
  - Round Robin with configurable time quantum
- Performance metrics calculation (waiting time, turnaround time)
- Average performance statistics
- Sample process dataset for demonstration
- Interactive menu-driven interface

## Scheduling Algorithms

### 1. FIFO (First-In-First-Out)
Processes are executed in the order they arrive. Simple but can lead to long waiting times for short processes that arrive after long ones.

### 2. SJF (Shortest Job First)
Processes with the shortest CPU burst time are executed first. Minimizes average waiting time but can cause starvation for long processes.

### 3. Priority Scheduling
Processes are executed based on priority levels. Lower numerical values indicate higher priority. Can suffer from indefinite blocking of low-priority processes.

### 4. Round Robin
Each process is given a fixed time quantum to execute. If it doesn't complete, it's placed at the end of the queue. Provides fair CPU sharing but has overhead from context switching.

## Standard Library Functions Used
- `stdio.h` - For input/output operations
- `stdlib.h` - For standard library functions and memory management
- `string.h` - For string manipulation
- `time.h` - For time-related functions

## How to Compile and Run

### Compilation
```bash
gcc -o scheduler main.c
```

### Execution
```bash
./scheduler
```

On Windows:
```bash
scheduler.exe
```

## How to Use
1. Run the program
2. Select a scheduling algorithm from the menu
3. For Round Robin, enter the time quantum when prompted
4. View the simulation results including:
   - Process execution order
   - Waiting times for each process
   - Turnaround times for each process
   - Average waiting and turnaround times
5. Compare different algorithms
6. Exit the program when finished

## Sample Output
```
Process Scheduler Simulator
Simulates FIFO, SJF, Priority, and Round Robin scheduling algorithms

===== Process Scheduler Simulator =====
1. First-In-First-Out (FIFO)
2. Shortest Job First (SJF)
3. Priority Scheduling
4. Round Robin Scheduling
5. Exit
====================================
Enter your choice: 2

=== Shortest Job First (SJF) Scheduling ===

PID   Name       Arrival  Burst    Waiting  Turnaround  Start     Finish
------------------------------------------------------------------------
2     Compiler   1        4        0        4           1         5
5     Antivirus  4        2        1        3           5         7
4     Database   3        5        4        9           7         12
1     TextEdit   0        8        12       20          12        20
3     Browser    2        9        16       25          20        29
------------------------------------------------------------------------
Average Waiting Time: 6.60
Average Turnaround Time: 12.20
```

## Educational Value
This implementation demonstrates:
1. Operating system process scheduling concepts
2. Algorithm implementation and comparison
3. Performance metrics calculation
4. Queue data structure usage
5. Process lifecycle management
6. Time complexity analysis of scheduling algorithms