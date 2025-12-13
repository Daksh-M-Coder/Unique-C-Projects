#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 10240  // 10KB memory pool
#define MIN_BLOCK_SIZE 16  // Minimum block size

// Structure to represent a memory block
typedef struct Block {
    size_t size;           // Size of the block
    bool free;             // Is the block free?
    struct Block* next;    // Pointer to next block
    struct Block* prev;    // Pointer to previous block
} Block;

// Global memory pool
static char memory_pool[POOL_SIZE];
static Block* head = NULL;

// Function prototypes
void init_memory_pool();
void* my_malloc(size_t size);
void my_free(void* ptr);
void print_memory_status();
Block* find_free_block(size_t size);
Block* split_block(Block* block, size_t size);
void merge_blocks();
void print_menu();

int main() {
    int choice;
    size_t size;
    void* ptr1, *ptr2, *ptr3;
    char continueOperation;

    // Initialize memory pool
    init_memory_pool();
    
    printf("Welcome to the Memory Allocator Implementation!\n");
    printf("Memory Pool Size: %d bytes\n", POOL_SIZE);

    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Allocate memory
                printf("Enter size to allocate (bytes): ");
                scanf("%zu", &size);
                ptr1 = my_malloc(size);
                if (ptr1 != NULL) {
                    printf("Allocated %zu bytes at address: %p\n", size, ptr1);
                } else {
                    printf("Failed to allocate %zu bytes\n", size);
                }
                break;

            case 2: // Free memory
                printf("Enter pointer address to free (in hex): ");
                scanf("%p", &ptr1);
                my_free(ptr1);
                printf("Memory freed\n");
                break;

            case 3: // Demo allocation
                printf("Demonstrating memory allocation...\n");
                
                // Allocate 3 blocks
                ptr1 = my_malloc(100);
                ptr2 = my_malloc(200);
                ptr3 = my_malloc(50);
                
                if (ptr1 && ptr2 && ptr3) {
                    printf("Allocated 100 bytes at: %p\n", ptr1);
                    printf("Allocated 200 bytes at: %p\n", ptr2);
                    printf("Allocated 50 bytes at: %p\n", ptr3);
                    
                    // Free middle block
                    my_free(ptr2);
                    printf("Freed middle block\n");
                    
                    // Allocate another block (should reuse freed space)
                    ptr2 = my_malloc(150);
                    if (ptr2) {
                        printf("Reallocated 150 bytes at: %p\n", ptr2);
                    } else {
                        printf("Failed to reallocate 150 bytes\n");
                    }
                } else {
                    printf("Allocation failed\n");
                }
                break;

            case 4: // Print memory status
                print_memory_status();
                break;

            case 5: // Exit
                printf("Thank you for using the Memory Allocator!\n");
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

// Initialize the memory pool
void init_memory_pool() {
    head = (Block*)memory_pool;
    head->size = POOL_SIZE - sizeof(Block);
    head->free = true;
    head->next = NULL;
    head->prev = NULL;
}

// Custom malloc implementation
void* my_malloc(size_t size) {
    // Align size to minimum block size
    if (size <= 0) return NULL;
    
    // Add space for block header
    size_t total_size = size + sizeof(Block);
    
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

// Custom free implementation
void my_free(void* ptr) {
    if (ptr == NULL) return;
    
    // Get block header (stored before the returned pointer)
    Block* block = (Block*)ptr - 1;
    
    // Mark block as free
    block->free = true;
    
    // Merge adjacent free blocks
    merge_blocks();
}

// Find a free block of sufficient size
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

// Split a block into two parts
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

// Merge adjacent free blocks
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

// Print memory status
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

// Print the menu
void print_menu() {
    printf("\n===== Memory Allocator =====\n");
    printf("1. Allocate memory\n");
    printf("2. Free memory\n");
    printf("3. Demo allocation\n");
    printf("4. Print memory status\n");
    printf("5. Exit\n");
    printf("===========================\n");
}