# Maze Solver using BFS Algorithm - Code Explanation

## Program Structure
The maze solver implements the Breadth-First Search (BFS) algorithm to find the shortest path in a maze. The program uses custom data structures to represent points, queue nodes, and queues, demonstrating how to implement fundamental algorithms and data structures in C without relying on external libraries.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
```
- `stdio.h`: For input/output operations
- `stdlib.h`: For program termination with `exit()`
- `stdbool.h`: For boolean data type support

### Constants and Data Structures
```c
#define MAX_SIZE 100

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point point;
    int distance;
} QueueNode;

typedef struct {
    QueueNode nodes[MAX_SIZE * MAX_SIZE];
    int front, rear;
} Queue;
```
- `MAX_SIZE`: Maximum dimensions for the maze
- `Point`: Represents coordinates in the maze
- `QueueNode`: Represents a node in the BFS queue with position and distance
- `Queue`: Implements a queue for BFS traversal

### Global Variables
```c
int maze[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int rows, cols;
Point start, end;
```
- `maze`: 2D array representing the maze layout
- `visited`: 2D array tracking visited cells and distances
- `rows`, `cols`: Dimensions of the maze
- `start`, `end`: Points representing start and end positions

## Detailed Code Walkthrough

### Queue Implementation
The program implements a queue from scratch since C doesn't have a built-in queue:

```c
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front > q->rear;
}

void enqueue(Queue* q, Point point, int distance) {
    q->rear++;
    q->nodes[q->rear].point = point;
    q->nodes[q->rear].distance = distance;
}

QueueNode dequeue(Queue* q) {
    QueueNode node = q->nodes[q->front];
    q->front++;
    return node;
}
```
- Simple array-based queue implementation
- `front` and `rear` pointers track the beginning and end
- `enqueue` adds elements to the rear
- `dequeue` removes elements from the front

### BFS Algorithm Implementation
The core of the program is the BFS implementation:

```c
bool bfs() {
    // Reset visited array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0;
        }
    }
    
    // Directions: up, right, down, left
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    
    Queue q;
    initQueue(&q);
    
    // Mark start point as visited and enqueue it
    visited[start.x][start.y] = 1;
    enqueue(&q, start, 0);
    
    while (!isEmpty(&q)) {
        QueueNode currentNode = dequeue(&q);
        Point currentPoint = currentNode.point;
        
        // If we reached the end point
        if (currentPoint.x == end.x && currentPoint.y == end.y) {
            return true;
        }
        
        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newX = currentPoint.x + dx[i];
            int newY = currentPoint.y + dy[i];
            
            if (isValid(newX, newY)) {
                visited[newX][newY] = visited[currentPoint.x][currentPoint.y] + 1;
                Point newPoint = {newX, newY};
                enqueue(&q, newPoint, currentNode.distance + 1);
            }
        }
    }
    
    return false;  // No path found
}
```

Key aspects of the BFS implementation:
1. **Initialization**: Reset visited array and initialize queue
2. **Direction Vectors**: `dx[]` and `dy[]` arrays for exploring neighbors
3. **Start Point**: Marked as visited and enqueued with distance 0
4. **Main Loop**: Continue while queue is not empty
5. **Goal Check**: Return true if end point is reached
6. **Neighbor Exploration**: Check all four directions (up, right, down, left)
7. **Distance Tracking**: Store distance in visited array for path reconstruction

### Validity Check
```c
bool isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}
```
Checks if a cell is:
- Within maze boundaries
- Not a wall (value 0)
- Not already visited

### Path Reconstruction
The `printPath()` function reconstructs the path by backtracking from the end point to the start point using the distance values stored in the visited array:

```c
int minDist = visited[x][y];
int nextX = x, nextY = y;

// Check neighbors to find the one with minimum distance
if (x > 0 && visited[x-1][y] < minDist && visited[x-1][y] != 0) {
    minDist = visited[x-1][y];
    nextX = x - 1; nextY = y;
}
// Similar checks for other directions...

if (!(nextX == start.x && nextY == start.y)) {
    pathMaze[nextX][nextY] = '*';  // Mark path
}
```

## Program Flow
1. Program starts and displays menu
2. User selects to solve sample maze
3. Sample maze is loaded into memory
4. BFS algorithm is executed
5. Results are displayed:
   - Original maze
   - Solution status (path found or not)
   - Path visualization if solution exists
6. User can continue or exit

## Learning Points
1. **Graph Algorithms**: Implementation of BFS for pathfinding
2. **Data Structures**: Custom queue implementation
3. **2D Array Manipulation**: Working with matrices
4. **Algorithm Design**: Step-by-step problem solving approach
5. **Backtracking**: Path reconstruction technique
6. **Boundary Checking**: Ensuring array accesses are valid
7. **State Tracking**: Using arrays to track visited nodes and distances

## Algorithm Complexity
- **Time Complexity**: O(rows × cols) - Each cell is visited at most once
- **Space Complexity**: O(rows × cols) - For the visited array and queue storage

## Possible Extensions
1. **Dynamic Maze Input**: Allow users to input custom mazes
2. **Multiple Algorithms**: Implement DFS or A* for comparison
3. **GUI Interface**: Create a graphical representation
4. **Performance Metrics**: Measure and display algorithm execution time
5. **Obstacle Types**: Different types of obstacles with varying costs