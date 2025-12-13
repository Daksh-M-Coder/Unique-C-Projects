# Memory Allocator Implementation

## Description
A custom memory allocator implementation that demonstrates how dynamic memory allocation works internally. This project implements a simplified version of malloc and free functions using a doubly-linked list of memory blocks. The allocator manages a fixed-size memory pool and supports allocation, deallocation, and memory coalescing.

## Features
- Custom implementation of malloc and free functions
- Memory pool management with fixed size (10KB)
- First-fit allocation strategy
- Block splitting for efficient memory usage
- Adjacent free block merging (coalescing)
- Memory status reporting
- Demonstration of memory allocation patterns

## Memory Management Concepts Demonstrated
1. **Memory Pool**: Fixed-size contiguous memory region
2. **Block Header**: Metadata stored with each memory block
3. **Free List**: Linked list of available memory blocks
4. **First-Fit Allocation**: Allocation strategy that uses the first suitable block
5. **Block Splitting**: Dividing large blocks to reduce waste
6. **Coalescing**: Merging adjacent free blocks to reduce fragmentation

## Data Structures Used
1. **Block Structure**: Represents a memory block with metadata
   ```c
   typedef struct Block {
       size_t size;           // Size of the block
       bool free;             // Is the block free?
       struct Block* next;    // Pointer to next block
       struct Block* prev;    // Pointer to previous block
   } Block;
   ```

## Standard Library Functions Used
- `stdio.h` - For input/output operations (`printf`, `scanf`)
- `stdlib.h` - For standard library functions (`exit`)
- `stdbool.h` - For boolean data type

## How to Compile and Run

### Compilation
```bash
gcc -o memory_allocator main.c
```

### Execution
```bash
./memory_allocator
```

On Windows:
```bash
memory_allocator.exe
```

## How to Use
1. Run the program
2. Select an operation from the menu:
   - Allocate memory: Request a specific amount of memory
   - Free memory: Release previously allocated memory
   - Demo allocation: Run a demonstration of allocation patterns
   - Print memory status: Display current memory pool state
   - Exit: Quit the program
3. Choose to continue or exit after each operation

## Sample Output
```
Welcome to the Memory Allocator Implementation!
Memory Pool Size: 10240 bytes

===== Memory Allocator =====
1. Allocate memory
2. Free memory
3. Demo allocation
4. Print memory status
5. Exit
===========================
Enter your choice: 3
Demonstrating memory allocation...
Allocated 100 bytes at: 0x55f8c8b8e020
Allocated 200 bytes at: 0x55f8c8b8e090
Allocated 50 bytes at: 0x55f8c8b8e160
Freed middle block
Reallocated 150 bytes at: 0x55f8c8b8e090
```

## Technical Details

### Memory Layout
The allocator maintains a doubly-linked list of memory blocks within a fixed-size memory pool. Each block contains:
- Size information
- Free/used status
- Pointers to adjacent blocks

### Allocation Process
1. Find the first free block of sufficient size
2. Split the block if it's significantly larger than needed
3. Mark the block as used
4. Return a pointer to the usable memory

### Deallocation Process
1. Mark the block as free
2. Merge with adjacent free blocks to reduce fragmentation

### Fragmentation Handling
The implementation includes coalescing to reduce external fragmentation by merging adjacent free blocks.

## Educational Value
This implementation demonstrates:
1. Memory management concepts
2. Linked data structures
3. Pointer manipulation
4. Memory layout and organization
5. Allocation algorithms
6. Fragmentation and its mitigation