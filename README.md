# 20 Professional C Programming Projects

This repository contains 20 professional C programming projects that demonstrate various aspects of the C language and standard library. Each project is contained in its own directory with:

- Source code files
- README.md with project description and usage instructions
- CODE_EXPLANATION.md with detailed code walkthrough

## Projects

### Original Projects (1-10)

1. [Number Guessing Game](./01_number_guessing_game/README.md) - Interactive game where player guesses a randomly generated number ✅ Completed
2. [Simple Calculator](./02_simple_calculator/README.md) - Command-line calculator supporting basic arithmetic operations ✅ Completed
3. [File Encryption/Decryption Tool](./03_file_encryption/README.md) - Utility for encrypting and decrypting files using XOR cipher ✅ Completed
4. [Contact Management System](./04_contact_manager/README.md) - Console-based contact manager with CRUD operations ✅ Completed
5. [Maze Solver](./05_maze_solver/README.md) - Maze solving program using Breadth-First Search algorithm ✅ Completed
6. [Weather Data Analyzer](./06_weather_analyzer/README.md) - Statistical analyzer for weather data files ✅ Completed
7. [Simple Banking System](./07_banking_system/README.md) - Basic banking system with account operations ✅ Completed
8. [Memory Allocator](./08_memory_allocator/README.md) - Custom implementation of dynamic memory allocation ✅ Completed
9. [Network Port Scanner](./09_port_scanner/README.md) - Simple TCP port scanner for network diagnostics ✅ Completed
10. [Chess Move Validator](./10_chess_validator/README.md) - Validator for legal chess moves ✅ Completed

### New Projects (11-20)

11. [Text-Based Adventure Game](./11_text_adventure/README.md) - Interactive fiction game with state management ✅ Completed
12. [Expression Evaluator](./12_expression_evaluator/README.md) - Mathematical expression parser and evaluator ✅ Completed
13. [PPM Image Processor](./13_ppm_processor/README.md) - Image processing tool for PPM format files ✅ Completed
14. [Process Scheduler](./14_process_scheduler/README.md) - Operating system process scheduling simulator ✅ Completed
15. [Compression Utility](./15_compression_utility/README.md) - File compression using Huffman coding ✅ Completed
16. [Database Engine](./16_database_engine/README.md) - Simple database with B+ tree indexing ✅ Completed
17. [Ray Tracer](./17_ray_tracer/README.md) - 3D rendering engine using ray tracing ✅ Completed
18. [Spreadsheet Engine](./18_spreadsheet_engine/README.md) - Spreadsheet application with formula evaluation ✅ Completed
19. [Compiler Lexer](./19_compiler_lexer/README.md) - Lexical analyzer for a subset of C language ✅ Completed
20. [Genetic Algorithm Framework](./20_genetic_algorithm/README.md) - Evolutionary computation framework ✅ Completed

## Prerequisites

- GCC compiler (MinGW on Windows)
- Standard C library

## Compilation

Each project can be compiled using GCC:

```bash
gcc -o project_name source_file.c
```

Or for projects with multiple source files:

```bash
gcc -o project_name *.c
```

Some projects may require linking the math library:

```bash
gcc -o project_name source_file.c -lm
```

## Project Summary

### Original Projects (1-10)

1. **Number Guessing Game** - Interactive game where players guess a randomly generated number
2. **Simple Calculator** - Command-line calculator with basic arithmetic and scientific functions
3. **File Encryption/Decryption Tool** - Utility for securing files using XOR cipher
4. **Contact Management System** - Console-based contact manager with persistent storage
5. **Maze Solver** - Maze solving program using Breadth-First Search algorithm
6. **Weather Data Analyzer** - Statistical analyzer for weather data files
7. **Simple Banking System** - Basic banking system with account operations
8. **Memory Allocator** - Custom implementation of dynamic memory allocation
9. **Network Port Scanner** - TCP port scanner for network diagnostics (cross-platform)
10. **Chess Move Validator** - Validator for legal chess moves according to standard rules

### New Projects (11-20)

11. **Text-Based Adventure Game** - Interactive fiction game with complex state management
12. **Expression Evaluator** - Mathematical expression parser using recursive descent
13. **PPM Image Processor** - Binary image file manipulation and processing
14. **Process Scheduler** - Operating system scheduling algorithms simulator
15. **Compression Utility** - Lossless file compression with Huffman encoding
16. **Database Engine** - Simple database with B+ tree indexing implementation
17. **Ray Tracer** - 3D graphics rendering using ray tracing techniques ✅ Completed
18. **Spreadsheet Engine** - Formula parsing and cell dependency management ✅ Completed
19. **Compiler Lexer** - Tokenization engine for programming language syntax ✅ Completed
20. **Genetic Algorithm Framework** - Evolutionary computing and optimization ✅ Completed

## Project Structure

Each project includes:
- A `main.c` file with complete implementation
- A `README.md` with project description, features, compilation instructions, and usage examples
- A `CODE_EXPLANATION.md` with detailed code walkthrough and technical explanations

## Key C Programming Concepts Covered

- **Basic I/O operations** (`printf`, `scanf`)
- **File handling** (text and binary files)
- **Data structures** (arrays, structs)
- **Dynamic memory management** (custom allocator)
- **String manipulation**
- **Mathematical operations**
- **Networking** (socket programming)
- **Algorithm implementation** (BFS, sorting, searching)
- **Error handling**
- **Cross-platform development**

All projects are ready to compile with MinGW on Windows using `gcc -o project_name main.c` (with appropriate flags where needed) and follow standard C programming practices.

For a complete overview of all 20 projects, see the [Project Summary](PROJECT_SUMMARY.md).

## Completion Status

🎉 **All 20 projects have been successfully completed!** 🎉

See the [Completion Notice](COMPLETION_NOTICE.md) for more details.