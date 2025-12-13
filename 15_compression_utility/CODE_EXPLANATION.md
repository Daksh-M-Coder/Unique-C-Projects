# Huffman Compression Utility - Code Explanation

## Program Structure
The Huffman compression utility implements the classic Huffman coding algorithm for lossless data compression. It analyzes character frequencies in input data, builds an optimal binary tree, generates variable-length codes, and compresses/decompresses files. The program includes both compression and decompression functionality with self-contained file format.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
```
- `stdio.h`: For file I/O operations
- `stdlib.h`: For memory allocation and standard library functions
- `string.h`: For string manipulation functions
- `stdint.h`: For fixed-width integer types

### Constants
```c
#define MAX_NODES 512
#define MAX_BITS 32
```
- Maximum number of nodes in Huffman tree
- Maximum bits per Huffman code

### Data Structures

#### Huffman Tree Node
```c
typedef struct {
    unsigned char data;
    int frequency;
    int left, right, parent;
    int is_leaf;
} Node;
```
- Represents a node in the Huffman tree
- Stores character data, frequency, and tree relationships
- `left`, `right`, `parent` are indices into node array
- `is_leaf` distinguishes leaf nodes (characters) from internal nodes

#### Huffman Code Structure
```c
typedef struct {
    unsigned char data;
    int code[MAX_BITS];
    int code_length;
} HuffmanCode;
```
- Stores generated Huffman codes for each character
- `code` array holds binary representation (0s and 1s)
- `code_length` tracks actual code length

### Global Variables
```c
Node nodes[MAX_NODES];
HuffmanCode codes[256];
int node_count = 0;
int code_count = 0;
```
- Global storage for Huffman tree and codes
- Counts track populated elements

## Detailed Code Walkthrough

### Main Function
```c
int main() {
    int choice;
    char input_file[256], output_file[256];
    
    printf("Huffman Compression Utility\n");
    // ... introductory messages ...
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Compress file
                compress_file(input_file, output_file);
                break;
            case 2:  // Decompress file
                decompress_file(input_file, output_file);
                break;
            case 3:  // Exit
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    
    return 0;
}
```
- Provides interactive menu-driven interface
- Handles user input and operation selection
- Controls program flow and termination

### Frequency Analysis
```c
void build_frequency_table(const char* data, int* freq_table) {
    // Initialize frequency table
    for (int i = 0; i < 256; i++) {
        freq_table[i] = 0;
    }
    
    // Count character frequencies
    int len = strlen(data);
    for (int i = 0; i < len; i++) {
        freq_table[(unsigned char)data[i]]++;
    }
}
```
- Calculates frequency of each byte value (0-255)
- Forms basis for optimal Huffman tree construction
- Handles all possible byte values in input data

### Huffman Tree Construction
```c
int build_huffman_tree(int* freq_table) {
    // Initialize nodes
    node_count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            nodes[node_count].data = (unsigned char)i;
            nodes[node_count].frequency = freq_table[i];
            nodes[node_count].left = -1;
            nodes[node_count].right = -1;
            nodes[node_count].parent = -1;
            nodes[node_count].is_leaf = 1;
            node_count++;
        }
    }
    
    // Build Huffman tree
    while (node_count > 1) {
        // Find two nodes with minimum frequency
        int min1 = -1, min2 = -1;
        int freq1 = 999999, freq2 = 999999;
        
        for (int i = 0; i < node_count; i++) {
            if (nodes[i].parent == -1) {  // Not yet merged
                if (nodes[i].frequency < freq1) {
                    freq2 = freq1;
                    min2 = min1;
                    freq1 = nodes[i].frequency;
                    min1 = i;
                } else if (nodes[i].frequency < freq2) {
                    freq2 = nodes[i].frequency;
                    min2 = i;
                }
            }
        }
        
        if (min1 == -1 || min2 == -1) break;
        
        // Create new internal node
        nodes[node_count].data = 0;
        nodes[node_count].frequency = freq1 + freq2;
        nodes[node_count].left = min1;
        nodes[node_count].right = min2;
        nodes[node_count].parent = -1;
        nodes[node_count].is_leaf = 0;
        
        // Update parent pointers
        nodes[min1].parent = node_count;
        nodes[min2].parent = node_count;
        
        node_count++;
    }
    
    return node_count - 1;  // Return root node index
}
```
- Creates leaf nodes for each character with non-zero frequency
- Iteratively merges two lowest-frequency nodes
- Creates internal nodes with combined frequencies
- Results in optimal prefix-free binary tree

### Code Generation
```c
void generate_codes(int root, int code[], int code_length) {
    if (root == -1) return;
    
    // If leaf node, store code
    if (nodes[root].is_leaf) {
        codes[code_count].data = nodes[root].data;
        codes[code_count].code_length = code_length;
        for (int i = 0; i < code_length; i++) {
            codes[code_count].code[i] = code[i];
        }
        code_count++;
        return;
    }
    
    // Traverse left (0)
    code[code_length] = 0;
    generate_codes(nodes[root].left, code, code_length + 1);
    
    // Traverse right (1)
    code[code_length] = 1;
    generate_codes(nodes[root].right, code, code_length + 1);
}
```
- Recursively traverses Huffman tree to generate codes
- Left edges represent 0 bits, right edges represent 1 bits
- Stores complete codes for each leaf node (character)
- Creates optimal variable-length encoding

### File Compression
```c
void compress_file(const char* input_filename, const char* output_filename) {
    FILE* input = fopen(input_filename, "rb");
    // ... file opening and error checking ...
    
    // Read entire file into memory
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    char* data = (char*)malloc(file_size + 1);
    // ... memory allocation and error checking ...
    
    fread(data, 1, file_size, input);
    data[file_size] = '\0';
    fclose(input);
    
    // Build frequency table
    int freq_table[256];
    build_frequency_table(data, freq_table);
    
    // Build Huffman tree
    int root = build_huffman_tree(freq_table);
    
    // Generate Huffman codes
    code_count = 0;
    int code[MAX_BITS];
    generate_codes(root, code, 0);
    
    // Write compressed file
    FILE* output = fopen(output_filename, "wb");
    // ... file opening and error checking ...
    
    // Write frequency table as header
    write_header(output, freq_table);
    
    // Compress data
    unsigned char bit_buffer = 0;
    int bit_count = 0;
    
    for (long i = 0; i < file_size; i++) {
        unsigned char ch = data[i];
        
        // Find Huffman code for character
        for (int j = 0; j < code_count; j++) {
            if (codes[j].data == ch) {
                // Write code bits
                for (int k = 0; k < codes[j].code_length; k++) {
                    bit_buffer |= (codes[j].code[k] << (7 - bit_count));
                    bit_count++;
                    
                    if (bit_count == 8) {
                        fwrite(&bit_buffer, 1, 1, output);
                        bit_buffer = 0;
                        bit_count = 0;
                    }
                }
                break;
            }
        }
    }
    
    // Write remaining bits
    if (bit_count > 0) {
        fwrite(&bit_buffer, 1, 1, output);
    }
    
    fclose(output);
    free(data);
    
    // Calculate compression ratio
    // ... file size comparison and ratio calculation ...
}
```
- Reads entire input file into memory
- Builds frequency table and Huffman tree
- Generates optimal codes for each character
- Packs bits efficiently into bytes for storage
- Includes frequency table in file header for decompression
- Calculates and displays compression statistics

### File Decompression
```c
void decompress_file(const char* input_filename, const char* output_filename) {
    FILE* input = fopen(input_filename, "rb");
    // ... file opening and error checking ...
    
    // Read frequency table from header
    int freq_table[256];
    if (!read_header(input, freq_table)) {
        printf("Error: Invalid compressed file format!\n");
        fclose(input);
        return;
    }
    
    // Build Huffman tree
    int root = build_huffman_tree(freq_table);
    
    // Read compressed data
    FILE* output = fopen(output_filename, "wb");
    // ... file opening and error checking ...
    
    // Decompress data
    int current_node = root;
    int bit_pos = 0;
    unsigned char byte;
    
    while (fread(&byte, 1, 1, input) == 1) {
        for (int i = 0; i < 8; i++) {
            int bit = (byte >> (7 - i)) & 1;
            
            if (bit == 0) {
                current_node = nodes[current_node].left;
            } else {
                current_node = nodes[current_node].right;
            }
            
            // If we reach a leaf node
            if (current_node != -1 && nodes[current_node].is_leaf) {
                fputc(nodes[current_node].data, output);
                current_node = root;
            }
        }
    }
    
    fclose(input);
    fclose(output);
    printf("File decompressed successfully!\n");
}
```
- Reads frequency table from compressed file header
- Reconstructs identical Huffman tree
- Decodes bitstream by traversing tree
- Outputs original characters when reaching leaf nodes
- Restores exact original data (lossless)

### File Format Handling
```c
void write_header(FILE* file, int* freq_table) {
    // Write frequency table
    fwrite(freq_table, sizeof(int), 256, file);
}

int read_header(FILE* file, int* freq_table) {
    // Read frequency table
    if (fread(freq_table, sizeof(int), 256, file) != 256) {
        return 0;  // Error reading header
    }
    return 1;  // Success
}
```
- Stores frequency table as 256 integers in file header
- Enables reconstruction of identical Huffman tree
- Simple but effective self-contained format

## Memory Management
- Dynamically allocates memory for file contents
- Uses fixed-size arrays for tree nodes and codes
- Frees allocated memory after compression
- Handles memory allocation errors gracefully

## Bit Manipulation
- Packs variable-length codes into bytes efficiently
- Uses bit shifting and masking for bit operations
- Handles partial bytes at end of compressed data
- Maintains bit alignment during encoding/decoding

## Program Flow
1. User selects compression or decompression
2. For compression:
   - Read input file
   - Analyze character frequencies
   - Build Huffman tree
   - Generate optimal codes
   - Encode data bit by bit
   - Write compressed file with header
3. For decompression:
   - Read header with frequency table
   - Rebuild identical Huffman tree
   - Decode bitstream by tree traversal
   - Write restored original file

## Learning Points
1. **Huffman Coding**: Classic algorithm for optimal prefix-free encoding
2. **Binary Trees**: Construction and traversal techniques
3. **Bit Manipulation**: Packing/unpacking variable-length codes
4. **File I/O**: Binary file operations and format design
5. **Memory Management**: Dynamic allocation and error handling
6. **Lossless Compression**: Principles and implementation

## Limitations and Possible Improvements
1. **Memory Usage**: Loads entire file into memory (limited by RAM)
2. **File Size**: Large files may not fit in available memory
3. **Speed**: Not optimized for maximum performance
4. **Adaptive Coding**: No adaptive frequency updates during compression
5. **Canonical Codes**: Doesn't use canonical Huffman codes for efficiency
6. **Error Recovery**: Limited error handling for corrupted files