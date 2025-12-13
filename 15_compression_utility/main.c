#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NODES 512
#define MAX_BITS 32

// Huffman tree node
typedef struct {
    unsigned char data;
    int frequency;
    int left, right, parent;
    int is_leaf;
} Node;

// Huffman code structure
typedef struct {
    unsigned char data;
    int code[MAX_BITS];
    int code_length;
} HuffmanCode;

// Global variables
Node nodes[MAX_NODES];
HuffmanCode codes[256];
int node_count = 0;
int code_count = 0;

// Function prototypes
void build_frequency_table(const char* data, int* freq_table);
int build_huffman_tree(int* freq_table);
void generate_codes(int root, int code[], int code_length);
void compress_file(const char* input_filename, const char* output_filename);
void decompress_file(const char* input_filename, const char* output_filename);
void write_header(FILE* file, int* freq_table);
int read_header(FILE* file, int* freq_table);
void print_menu();

int main() {
    int choice;
    char input_file[256], output_file[256];
    
    printf("Huffman Compression Utility\n");
    printf("Implements lossless data compression using Huffman coding\n\n");
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Compress file
                printf("Enter input filename: ");
                scanf("%s", input_file);
                printf("Enter output filename: ");
                scanf("%s", output_file);
                compress_file(input_file, output_file);
                break;
                
            case 2:  // Decompress file
                printf("Enter compressed filename: ");
                scanf("%s", input_file);
                printf("Enter output filename: ");
                scanf("%s", output_file);
                decompress_file(input_file, output_file);
                break;
                
            case 3:  // Exit
                printf("Goodbye!\n");
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

// Build frequency table for input data
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

// Build Huffman tree from frequency table
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

// Generate Huffman codes from tree
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

// Compress file using Huffman coding
void compress_file(const char* input_filename, const char* output_filename) {
    FILE* input = fopen(input_filename, "rb");
    if (!input) {
        printf("Error: Could not open input file!\n");
        return;
    }
    
    // Read entire file into memory
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    char* data = (char*)malloc(file_size + 1);
    if (!data) {
        printf("Error: Memory allocation failed!\n");
        fclose(input);
        return;
    }
    
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
    if (!output) {
        printf("Error: Could not create output file!\n");
        free(data);
        return;
    }
    
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
    FILE* original = fopen(input_filename, "rb");
    FILE* compressed = fopen(output_filename, "rb");
    fseek(original, 0, SEEK_END);
    fseek(compressed, 0, SEEK_END);
    long orig_size = ftell(original);
    long comp_size = ftell(compressed);
    fclose(original);
    fclose(compressed);
    
    printf("File compressed successfully!\n");
    printf("Original size: %ld bytes\n", orig_size);
    printf("Compressed size: %ld bytes\n", comp_size);
    printf("Compression ratio: %.2f%%\n", (1.0 - (double)comp_size / orig_size) * 100);
}

// Decompress file using Huffman tree
void decompress_file(const char* input_filename, const char* output_filename) {
    FILE* input = fopen(input_filename, "rb");
    if (!input) {
        printf("Error: Could not open input file!\n");
        return;
    }
    
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
    if (!output) {
        printf("Error: Could not create output file!\n");
        fclose(input);
        return;
    }
    
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

// Write frequency table as header
void write_header(FILE* file, int* freq_table) {
    // Write frequency table
    fwrite(freq_table, sizeof(int), 256, file);
}

// Read frequency table from header
int read_header(FILE* file, int* freq_table) {
    // Read frequency table
    if (fread(freq_table, sizeof(int), 256, file) != 256) {
        return 0;  // Error reading header
    }
    return 1;  // Success
}

// Print menu
void print_menu() {
    printf("\n===== Huffman Compression Utility =====\n");
    printf("1. Compress file\n");
    printf("2. Decompress file\n");
    printf("3. Exit\n");
    printf("==================================\n");
}