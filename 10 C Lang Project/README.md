# 10 Professional C Programming Projects

This repository contains 10 professional C programming projects that demonstrate various aspects of the C language and standard library. Each project is contained in its own directory with:

- Source code files
- README.md with project description and usage instructions
- CODE_EXPLANATION.md with detailed code walkthrough

## Projects

1. [Number Guessing Game](./01_number_guessing_game/README.md) - Interactive game where player guesses a randomly generated number
2. [Simple Calculator](./02_simple_calculator/README.md) - Command-line calculator supporting basic arithmetic operations
3. [File Encryption/Decryption Tool](./03_file_encryption/README.md) - Utility for encrypting and decrypting files using XOR cipher
4. [Contact Management System](./04_contact_manager/README.md) - Console-based contact manager with CRUD operations
5. [Maze Solver](./05_maze_solver/README.md) - Maze solving program using Breadth-First Search algorithm
6. [Weather Data Analyzer](./06_weather_analyzer/README.md) - Statistical analyzer for weather data files
7. [Simple Banking System](./07_banking_system/README.md) - Basic banking system with account operations
8. [Memory Allocator](./08_memory_allocator/README.md) - Custom implementation of dynamic memory allocation
9. [Network Port Scanner](./09_port_scanner/README.md) - Simple TCP port scanner for network diagnostics
10. [Chess Move Validator](./10_chess_validator/README.md) - Validator for legal chess moves

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