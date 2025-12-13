# Huffman Compression Utility

## Description
A lossless data compression utility that implements Huffman coding algorithm. The program can compress any file by analyzing character frequencies and creating optimal binary codes. It also provides decompression functionality to restore original files exactly.

## Features
- Lossless Huffman compression algorithm implementation
- Frequency analysis of input data
- Optimal binary code generation
- File compression and decompression
- Compression ratio calculation
- Self-contained format (includes frequency table in compressed file)
- Support for all byte values (0-255)

## Huffman Coding Algorithm
Huffman coding is a lossless compression algorithm that uses variable-length codes for different characters. Characters that appear more frequently are assigned shorter codes, while less frequent characters get longer codes. This results in overall data reduction.

The algorithm works as follows:
1. Calculate frequency of each character in input data
2. Build a binary tree (Huffman tree) based on frequencies
3. Assign binary codes by traversing the tree (left=0, right=1)
4. Encode data using generated codes
5. Store frequency table in compressed file header for decompression

## Standard Library Functions Used
- `stdio.h` - For file I/O operations
- `stdlib.h` - For memory allocation and standard library functions
- `string.h` - For string manipulation
- `stdint.h` - For fixed-width integer types

## How to Compile and Run

### Compilation
```bash
gcc -o compressor main.c
```

### Execution
```bash
./compressor
```

On Windows:
```bash
compressor.exe
```

## How to Use
1. Run the program
2. Select operation from the menu:
   - Compress file: Analyze input file and create compressed version
   - Decompress file: Restore original file from compressed version
   - Exit: Quit the program
3. For compression:
   - Enter input filename (any file type)
   - Enter output filename for compressed data
4. For decompression:
   - Enter compressed filename
   - Enter output filename for restored data
5. View compression statistics after compression

## Sample Usage
```
Huffman Compression Utility
Implements lossless data compression using Huffman coding

===== Huffman Compression Utility =====
1. Compress file
2. Decompress file
3. Exit
==================================
Enter your choice: 1
Enter input filename: document.txt
Enter output filename: document.huff
File compressed successfully!
Original size: 10240 bytes
Compressed size: 6144 bytes
Compression ratio: 40.00%

Enter your choice: 2
Enter compressed filename: document.huff
Enter output filename: document_restored.txt
File decompressed successfully!
```

## File Format
The compressed file format includes:
1. Header: 256 integers representing frequency table
2. Body: Huffman-encoded bitstream of original data

## Educational Value
This implementation demonstrates:
1. Huffman coding algorithm implementation
2. Binary tree construction and traversal
3. Variable-length encoding techniques
4. Bit manipulation for efficient storage
5. Lossless data compression principles
6. File format design with embedded metadata