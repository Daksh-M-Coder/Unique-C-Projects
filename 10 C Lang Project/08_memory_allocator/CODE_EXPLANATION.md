# Memory Allocator Implementation - Code Explanation

## Program Structure
The memory allocator implementation demonstrates how dynamic memory allocation works internally by implementing a simplified version of malloc and free functions. It uses a doubly-linked list of memory blocks within a fixed-size memory pool to manage allocations and deallocations.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
```
- `stdio.h`: For input/output operations
- `stdlib.h`: For standard library functions like `exit()`
- `stdbool.h`: For boolean data type support

### Constants
```c
#define POOL_SIZE 10240  // 10KB memory pool
#define MIN_BLOCK_SIZE 16  // Minimum block size
```
- `POOL_SIZE`: Size of the fixed memory pool
- `MIN_BLOCK_SIZE`: Minimum size for memory blocks to reduce fragmentation

### Data Structures
```c
typedef struct Block {
    size_t size;           // Size of the block
    bool free;             // Is the block free?
    struct Block* next;    // Pointer to next block
    struct Block* prev;    // Pointer to previous block
} Block;
```
- `Block`: Represents a memory block with metadata
- `size`: Size of the usable memory in the block
- `free`: Boolean indicating if the block is allocated or free
- `next`, `prev`: Pointers for doubly-linked list structure

### Global Variables
```c
static char memory_pool[POOL_SIZE];
static Block* head = NULL;
```
- `memory_pool`: Fixed-size array representing the memory pool
- `head`: Pointer to the first block in the linked list

### Function Prototypes
```c
void init_memory_pool();
void* my_malloc(size_t size);
void my_free(void* ptr);
void print_memory_status();
Block* find_free_block(size_t size);
Block* split_block(Block* block, size_t size);
void merge_blocks();
void print_menu();
```
Each function handles a specific aspect of memory management or UI.

## Detailed Code Walkthrough

### Memory Pool Initialization
```c
void init_memory_pool() {
    head = (Block*)memory_pool;
    head->size = POOL_SIZE - sizeof(Block);
    head->free = true;
    head->next = NULL;
    head->prev = NULL;
}
```
- Initializes the memory pool as one large free block
- Sets up the first block to occupy the entire pool minus its header size
- Marks the block as free and initializes list pointers

### Custom Malloc Implementation
```c
void* my_malloc(size_t size) {
    // Align size to minimum block size
    if (size <= 0) return NULL;
    
    // Find a free block
    Block* block = find_free_block(size);
    
    if (block == NULL) {
        return NULL;  // No free block found
    }
    
    // Split block if it's much larger than needed
    if (block->size >= size + sizeof(Block) + MIN_BLOCK_SIZE) {
        block = split_block(block, size);
    }
    
    block->free = false;
    
    // Return pointer to memory after the block header
    return (void*)(block + 1);
}
```
Key aspects:
1. **Validation**: Checks for valid size requests
2. **Block Finding**: Uses first-fit strategy to locate suitable free block
3. **Block Splitting**: Divides large blocks to reduce waste
4. **Allocation**: Marks block as used and returns usable memory pointer

### Custom Free Implementation
```c
void my_free(void* ptr) {
    if (ptr == NULL) return;
    
    // Get block header (stored before the returned pointer)
    Block* block = (Block*)ptr - 1;
    
    // Mark block as free
    block->free = true;
    
    // Merge adjacent free blocks
    merge_blocks();
}
```
Key aspects:
1. **Null Check**: Handles NULL pointer gracefully
2. **Header Access**: Calculates block header location from returned pointer
3. **Deallocation**: Marks block as free
4. **Coalescing**: Merges adjacent free blocks to reduce fragmentation

### First-Fit Block Finding
```c
Block* find_free_block(size_t size) {
    Block* current = head;
    
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;  // No suitable block found
}
```
- Traverses the linked list from head
- Returns the first free block that can accommodate the requested size
- Returns NULL if no suitable block is found

### Block Splitting
```c
Block* split_block(Block* block, size_t size) {
    size_t remaining_size = block->size - size - sizeof(Block);
    
    // Only split if remaining block is large enough
    if (remaining_size >= MIN_BLOCK_SIZE) {
        Block* new_block = (Block*)((char*)block + sizeof(Block) + size);
        new_block->size = remaining_size;
        new_block->free = true;
        new_block->next = block->next;
        new_block->prev = block;
        
        if (block->next != NULL) {
            block->next->prev = new_block;
        }
        
        block->next = new_block;
        block->size = size;
    }
    
    return block;
}
```
- Calculates remaining space after allocation
- Creates a new block only if it meets minimum size requirements
- Updates linked list pointers for both blocks
- Adjusts sizes of both blocks

### Block Merging (Coalescing)
```c
void merge_blocks() {
    Block* current = head;
    
    while (current != NULL && current->next != NULL) {
        // If both current and next blocks are free, merge them
        if (current->free && current->next->free) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
            
            if (current->next != NULL) {
                current->next->prev = current;
            }
        } else {
            current = current->next;
        }
    }
}
```
- Traverses the linked list
- Merges adjacent free blocks by combining their sizes
- Updates linked list pointers to remove merged blocks
- Preserves list integrity during merging

### Memory Status Reporting
```c
void print_memory_status() {
    printf("\n===== Memory Pool Status =====\n");
    printf("Address\t\tSize\tFree\n");
    printf("--------------------------------\n");
    
    Block* current = head;
    int block_count = 0;
    size_t total_free = 0;
    size_t total_used = 0;
    
    while (current != NULL) {
        printf("%p\t%zu\t%s\n", 
               (void*)current, 
               current->size, 
               current->free ? "Yes" : "No");
        
        if (current->free) {
            total_free += current->size;
        } else {
            total_used += current->size;
        }
        
        block_count++;
        current = current->next;
    }
    
    printf("\nTotal blocks: %d\n", block_count);
    printf("Total free memory: %zu bytes\n", total_free);
    printf("Total used memory: %zu bytes\n", total_used);
    printf("Memory pool size: %d bytes\n", POOL_SIZE);
}
```
- Displays detailed information about each block
- Shows address, size, and allocation status
- Calculates and displays summary statistics
- Helps visualize memory layout and fragmentation

## Memory Layout Explanation
```
Memory Pool:
[Block Header][Usable Memory][Block Header][Usable Memory]...
^             ^               ^
|             |               |
Block*        Returned ptr    Next Block
```
- Each block consists of a header followed by usable memory
- The returned pointer points to the usable memory, not the header
- Block headers are accessed by subtracting 1 from the returned pointer

## Program Flow
1. Initialize memory pool as one large free block
2. Present menu to user for operations
3. Handle allocation requests:
   - Find suitable free block
   - Split if necessary
   - Mark as used
   - Return pointer to usable memory
4. Handle deallocation requests:
   - Mark block as free
   - Merge adjacent free blocks
5. Display memory status when requested
6. Continue until user exits

## Learning Points
1. **Memory Management**: Understanding how malloc/free work internally
2. **Linked Lists**: Doubly-linked list implementation and manipulation
3. **Pointer Arithmetic**: Calculating memory addresses and offsets
4. **Data Structures**: Block header design and metadata management
5. **Algorithms**: First-fit allocation strategy
6. **Fragmentation**: Internal and external fragmentation concepts
7. **Coalescing**: Reducing fragmentation through block merging

## Limitations and Possible Improvements
1. **Single Threaded**: Not thread-safe for concurrent access
2. **Fixed Pool Size**: Uses static memory pool rather than system heap
3. **First-Fit Only**: Could implement best-fit or worst-fit strategies
4. **No Alignment**: Doesn't handle memory alignment requirements
5. **No Error Recovery**: Limited error handling for corrupted metadata
6. **Performance**: Linear search for allocation; could use free lists sorted by size
7. **No Reallocation**: Missing realloc functionality