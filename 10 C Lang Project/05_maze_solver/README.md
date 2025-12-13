# Maze Solver using BFS Algorithm

## Description
A maze solver that uses the Breadth-First Search (BFS) algorithm to find the shortest path between a start and end point in a maze. The program demonstrates graph traversal techniques and pathfinding algorithms commonly used in game development and robotics.

## Features
- Implementation of BFS algorithm for shortest path finding
- Visualization of maze and solution path
- Sample maze included for demonstration
- Queue-based implementation of BFS
- Path reconstruction from destination to start

## Algorithm Overview
Breadth-First Search (BFS) is an algorithm for traversing or searching tree or graph data structures. It starts at the root node and explores all neighbor nodes at the present depth prior to moving on to nodes at the next depth level. In the context of maze solving, BFS guarantees finding the shortest path if one exists.

## Data Structures Used
1. **Point Structure**: Represents coordinates (x, y) in the maze
2. **QueueNode Structure**: Represents a node in the BFS queue with position and distance
3. **Queue Structure**: Implements a queue for BFS traversal
4. **2D Arrays**: 
   - `maze[][]`: Represents the maze layout (0 = path, 1 = wall)
   - `visited[][]`: Tracks visited cells and distances

## Standard Library Functions Used
- `stdio.h` - For input/output operations (`printf`, `scanf`)
- `stdlib.h` - For program termination (`exit`)
- `stdbool.h` - For boolean data type

## How to Compile and Run

### Compilation
```bash
gcc -o maze_solver main.c
```

### Execution
```bash
./maze_solver
```

On Windows:
```bash
maze_solver.exe
```

## How to Use
1. Run the program
2. Select option 1 to solve the sample maze
3. View the maze layout, solution status, and path visualization
4. Choose to continue or exit

## Sample Maze
The program includes a sample 5x5 maze:
```
S # . . .
. # . # .
. . . # .
# # . . .
. . . # E
```
Where:
- S = Start point
- E = End point
- # = Wall
- . = Path

## Sample Output
```
Welcome to the Maze Solver using BFS Algorithm!

===== Maze Solver using BFS =====
1. Solve sample maze
2. Exit
================================
Enter your choice: 1

Sample Maze:
S # . . . 
. # . # . 
. . . # . 
# # . . . 
. . . # E 

Path found!

Path visualization:
S # * * * 
. # * # * 
. . * # * 
# # * . * 
. . * # E 
```

## Algorithm Details
1. **Initialization**: Start point is marked as visited with distance 0
2. **Queue Operations**: Start point is enqueued
3. **Exploration**: While queue is not empty:
   - Dequeue a cell
   - If it's the destination, path is found
   - Otherwise, enqueue all unvisited neighbors
4. **Path Reconstruction**: Trace back from end to start using distance values

## Time and Space Complexity
- **Time Complexity**: O(rows × cols) - Each cell is visited at most once
- **Space Complexity**: O(rows × cols) - For the visited array and queue storage

## Educational Value
This implementation demonstrates:
1. Graph traversal algorithms
2. Queue data structure implementation
3. Pathfinding techniques
4. 2D array manipulation
5. Backtracking for path reconstruction