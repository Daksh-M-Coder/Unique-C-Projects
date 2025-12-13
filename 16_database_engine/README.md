# Simple Database Engine

## Description
A simple database engine that implements basic relational database functionality with B+ tree indexing. The program supports table creation, field definition, record insertion, querying by ID, and indexed searches. It demonstrates fundamental database concepts including schema management, data storage, and indexing.

## Features
- Table creation and schema management
- Field definition with string and integer types
- Record insertion and retrieval
- Primary key-based record lookup
- B+ tree indexing (simplified implementation)
- Indexed search operations
- Database persistence (save/load)
- Interactive command-line interface

## Database Concepts Implemented

### Tables and Schemas
- Logical table organization
- Field definitions with data types
- Schema validation and management

### Records and Storage
- Fixed-size record storage
- Linked list for free space management
- Direct record access by ID

### Indexing
- B+ tree indexing concept (simplified)
- Key-based record lookup
- Index maintenance during insertions

### Persistence
- Binary serialization of database state
- File-based storage and retrieval

## Standard Library Functions Used
- `stdio.h` - For file I/O operations and standard input/output
- `stdlib.h` - For memory management and standard library functions
- `string.h` - For string manipulation and memory operations
- `stdbool.h` - For boolean data type support

## How to Compile and Run

### Compilation
```bash
gcc -o database main.c
```

### Execution
```bash
./database
```

On Windows:
```bash
database.exe
```

## How to Use
1. Run the program
2. Create tables and define their schemas
3. Insert records into tables
4. Query records by ID or through indexes
5. Save database state to file
6. Load database from file
7. Exit the program

## Sample Usage
```
Simple Database Engine with B+ Tree Indexing
Supports basic CRUD operations and indexing

===== Database Engine =====
1. Create table
2. Add field to table
3. Insert record
4. Find record by ID
5. Create index
6. Search by index
7. Print table schema
8. Print all records
9. Save database
10. Load database
11. Exit
=========================
Enter your choice: 1
Enter table name: employees
Table 'employees' created successfully!

Enter your choice: 2
Enter table ID (0-0): 0
Enter field name: name
Enter field type (0=string, 1=integer): 0
Field added successfully!

Enter your choice: 2
Enter table ID (0-0): 0
Enter field name: salary
Enter field type (0=string, 1=integer): 1
Field added successfully!
```

## Data Structures
1. **Field**: Represents column definition with name and type
2. **Record**: Data row with values and linking information
3. **IndexEntry**: Key-value pair for indexed lookups
4. **Table**: Collection of fields, records, and indexes
5. **Database**: Collection of tables

## Educational Value
This implementation demonstrates:
1. Relational database fundamentals
2. B+ tree indexing concepts
3. Data structure design for databases
4. Memory management techniques
5. File persistence strategies
6. CRUD operations implementation