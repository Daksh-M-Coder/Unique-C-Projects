#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Structure to represent a point in the maze
typedef struct {
    int x, y;
} Point;

// Structure to represent a queue node for BFS
typedef struct {
    Point point;
    int distance;
} QueueNode;

// Queue structure for BFS
typedef struct {
    QueueNode nodes[MAX_SIZE * MAX_SIZE];
    int front, rear;
} Queue;

// Maze representation
int maze[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int rows, cols;
Point start, end;

// Function prototypes
void initQueue(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, Point point, int distance);
QueueNode dequeue(Queue* q);
bool isValid(int x, int y);
bool bfs();
void printMaze();
void printPath();
void printMenu();

int main() {
    int choice;
    char continueOperation;

    printf("Welcome to the Maze Solver using BFS Algorithm!\n");

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Solve sample maze
                // Define a sample maze (0 = path, 1 = wall)
                rows = 5;
                cols = 5;
                
                int sampleMaze[5][5] = {
                    {0, 1, 0, 0, 0},
                    {0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0},
                    {1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 0}
                };
                
                // Copy sample maze to main maze
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        maze[i][j] = sampleMaze[i][j];
                    }
                }
                
                start.x = 0; start.y = 0;  // Start point
                end.x = rows - 1; end.y = cols - 1;  // End point
                
                printf("\nSample Maze:\n");
                printMaze();
                
                if (bfs()) {
                    printf("\nPath found!\n");
                    printPath();
                } else {
                    printf("\nNo path found!\n");
                }
                break;
            }

            case 2: // Exit
                printf("Thank you for using the Maze Solver!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &continueOperation);
        printf("\n");

    } while (continueOperation == 'y' || continueOperation == 'Y');

    return 0;
}

// Initialize queue
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return q->front > q->rear;
}

// Add element to queue
void enqueue(Queue* q, Point point, int distance) {
    q->rear++;
    q->nodes[q->rear].point = point;
    q->nodes[q->rear].distance = distance;
}

// Remove element from queue
QueueNode dequeue(Queue* q) {
    QueueNode node = q->nodes[q->front];
    q->front++;
    return node;
}

// Check if a point is valid (within bounds and not a wall)
bool isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}

// BFS algorithm to find shortest path
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

// Print the maze
void printMaze() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == start.x && j == start.y) {
                printf("S ");  // Start point
            } else if (i == end.x && j == end.y) {
                printf("E ");  // End point
            } else if (maze[i][j] == 1) {
                printf("# ");  // Wall
            } else {
                printf(". ");  // Path
            }
        }
        printf("\n");
    }
}

// Print the path from start to end
void printPath() {
    printf("\nPath visualization:\n");
    
    // Create a copy of the maze for path visualization
    char pathMaze[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == start.x && j == start.y) {
                pathMaze[i][j] = 'S';
            } else if (i == end.x && j == end.y) {
                pathMaze[i][j] = 'E';
            } else if (maze[i][j] == 1) {
                pathMaze[i][j] = '#';
            } else {
                pathMaze[i][j] = '.';
            }
        }
    }
    
    // Mark the path
    int x = end.x, y = end.y;
    while (!(x == start.x && y == start.y)) {
        int minDist = visited[x][y];
        int nextX = x, nextY = y;
        
        // Check neighbors to find the one with minimum distance
        if (x > 0 && visited[x-1][y] < minDist && visited[x-1][y] != 0) {
            minDist = visited[x-1][y];
            nextX = x - 1; nextY = y;
        }
        if (x < rows-1 && visited[x+1][y] < minDist && visited[x+1][y] != 0) {
            minDist = visited[x+1][y];
            nextX = x + 1; nextY = y;
        }
        if (y > 0 && visited[x][y-1] < minDist && visited[x][y-1] != 0) {
            minDist = visited[x][y-1];
            nextX = x; nextY = y - 1;
        }
        if (y < cols-1 && visited[x][y+1] < minDist && visited[x][y+1] != 0) {
            minDist = visited[x][y+1];
            nextX = x; nextY = y + 1;
        }
        
        if (!(nextX == start.x && nextY == start.y)) {
            pathMaze[nextX][nextY] = '*';  // Mark path
        }
        
        x = nextX; y = nextY;
    }
    
    // Print the maze with path
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", pathMaze[i][j]);
        }
        printf("\n");
    }
}

// Print the menu
void printMenu() {
    printf("\n===== Maze Solver using BFS =====\n");
    printf("1. Solve sample maze\n");
    printf("2. Exit\n");
    printf("================================\n");
}