# Simple Database Engine - Code Explanation

## Program Structure
The simple database engine implements fundamental relational database concepts including tables, records, fields, and indexing. It uses data structures to represent database entities and provides basic CRUD operations. The implementation includes a simplified B+ tree index and binary file persistence.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
```
- `stdio.h`: For file I/O operations and standard input/output
- `stdlib.h`: For memory management and standard library functions
- `string.h`: For string manipulation and memory operations
- `stdbool.h`: For boolean data type support

### Constants
```c
#define MAX_RECORDS 1000
#define MAX_FIELDS 10
#define MAX_FIELD_NAME 32
#define MAX_FIELD_VALUE 256
#define MAX_INDEX_ENTRIES 1000
```
- Maximum limits for database entities to prevent memory issues
- Buffer sizes for names and values

### Data Structures

#### Field Structure
```c
typedef struct {
    char name[MAX_FIELD_NAME];
    int type;  // 0 = string, 1 = integer
} Field;
```
- Represents a column definition in a table
- Stores field name and data type

#### Record Structure
```c
typedef struct {
    int id;
    char values[MAX_FIELDS][MAX_FIELD_VALUE];
    int next;  // For linked list of records
} Record;
```
- Represents a data row in a table
- Contains field values and linking information for free list

#### Index Entry Structure
```c
typedef struct {
    char key[MAX_FIELD_VALUE];
    int record_id;
} IndexEntry;
```
- Represents a key-value pair for indexed lookups
- Maps search keys to record IDs

#### Table Structure
```c
typedef struct {
    char name[32];
    Field fields[MAX_FIELDS];
    int field_count;
    Record records[MAX_RECORDS];
    int record_count;
    int free_list;  // Head of free record list
    IndexEntry index[MAX_INDEX_ENTRIES];
    int index_count;
    int indexed_field;  // Field index for B+ tree (simplified)
} Table;
```
- Represents a database table with schema and data
- Manages records, fields, and indexes
- Uses linked list for efficient space management

#### Database Structure
```c
typedef struct {
    Table tables[10];
    int table_count;
} Database;
```
- Top-level database container
- Manages multiple tables

## Detailed Code Walkthrough

### Main Function
```c
int main() {
    Database db;
    int choice, table_id, field_type;
    char table_name[32], field_name[32];
    // ... other variables ...
    
    init_database(&db);
    
    printf("Simple Database Engine with B+ Tree Indexing\n");
    // ... introductory messages ...
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Create table
                create_table(&db, table_name);
                break;
            case 2:  // Add field
                add_field(&db.tables[table_id], field_name, field_type);
                break;
            // ... other cases ...
            case 11:  // Exit
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

### Database Initialization
```c
void init_database(Database* db) {
    db->table_count = 0;
    
    // Initialize free lists for all tables
    for (int i = 0; i < 10; i++) {
        db->tables[i].record_count = 0;
        db->tables[i].free_list = -1;
        db->tables[i].index_count = 0;
        db->tables[i].indexed_field = -1;
        
        // Initialize free list for records
        for (int j = 0; j < MAX_RECORDS - 1; j++) {
            db->tables[i].records[j].next = j + 1;
        }
        db->tables[i].records[MAX_RECORDS - 1].next = -1;
        db->tables[i].free_list = 0;
    }
}
```
- Initializes database state and free lists
- Sets up linked list structure for efficient record allocation
- Prepares data structures for table creation

### Table Management
```c
Table* create_table(Database* db, const char* name) {
    if (db->table_count >= 10) {
        return NULL;
    }
    
    Table* table = &db->tables[db->table_count];
    strncpy(table->name, name, sizeof(table->name) - 1);
    table->name[sizeof(table->name) - 1] = '\0';
    table->field_count = 0;
    table->record_count = 0;
    table->index_count = 0;
    table->indexed_field = -1;
    
    db->table_count++;
    return table;
}
```
- Creates new table with specified name
- Initializes table metadata
- Returns pointer to created table

### Field Management
```c
int add_field(Table* table, const char* name, int type) {
    if (table->field_count >= MAX_FIELDS) {
        return 0;  // Too many fields
    }
    
    Field* field = &table->fields[table->field_count];
    strncpy(field->name, name, sizeof(field->name) - 1);
    field->name[sizeof(field->name) - 1] = '\0';
    field->type = type;
    
    table->field_count++;
    return 1;  // Success
}
```
- Adds field definition to table schema
- Validates field count limits
- Stores field name and type

### Record Management
```c
int insert_record(Table* table, const char* values[]) {
    if (table->free_list == -1) {
        return -1;  // No free records
    }
    
    // Get a free record
    int record_id = table->free_list;
    Record* record = &table->records[record_id];
    table->free_list = record->next;  // Update free list
    
    // Set record data
    record->id = record_id;
    for (int i = 0; i < table->field_count; i++) {
        strncpy(record->values[i], values[i], sizeof(record->values[i]) - 1);
        record->values[i][sizeof(record->values[i]) - 1] = '\0';
    }
    
    // Add to index if indexing is enabled
    if (table->indexed_field >= 0) {
        if (table->index_count < MAX_INDEX_ENTRIES) {
            IndexEntry* entry = &table->index[table->index_count];
            strncpy(entry->key, record->values[table->indexed_field], 
                    sizeof(entry->key) - 1);
            entry->key[sizeof(entry->key) - 1] = '\0';
            entry->record_id = record_id;
            table->index_count++;
        }
    }
    
    table->record_count++;
    return record_id;
}
```
- Allocates record from free list
- Populates record with provided values
- Updates index if field is indexed
- Maintains record count and free list

### Record Retrieval
```c
Record* find_record(Table* table, int id) {
    if (id < 0 || id >= MAX_RECORDS) {
        return NULL;
    }
    
    Record* record = &table->records[id];
    if (record->id == id) {
        return record;
    }
    
    return NULL;
}
```
- Retrieves record by ID in O(1) time
- Validates record ID and existence
- Returns pointer to record or NULL

### Indexing
```c
void create_index(Table* table, int field_index) {
    table->indexed_field = field_index;
    table->index_count = 0;
    
    // Build index from existing records
    for (int i = 0; i < MAX_RECORDS; i++) {
        Record* record = &table->records[i];
        if (record->id == i) {  // Valid record
            if (table->index_count < MAX_INDEX_ENTRIES) {
                IndexEntry* entry = &table->index[table->index_count];
                strncpy(entry->key, record->values[field_index], 
                        sizeof(entry->key) - 1);
                entry->key[sizeof(entry->key) - 1] = '\0';
                entry->record_id = i;
                table->index_count++;
            }
        }
    }
}

Record* find_by_index(Table* table, const char* key) {
    if (table->indexed_field == -1) {
        return NULL;  // No index
    }
    
    // Linear search through index (simplified B+ tree lookup)
    for (int i = 0; i < table->index_count; i++) {
        if (strcmp(table->index[i].key, key) == 0) {
            int record_id = table->index[i].record_id;
            return &table->records[record_id];
        }
    }
    
    return NULL;  // Not found
}
```
- Creates index on specified field
- Builds index from existing records
- Provides indexed lookup (simplified B+ tree)
- Linear search through index entries

### Persistence
```c
void save_database(Database* db, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Could not create file!\n");
        return;
    }
    
    fwrite(db, sizeof(Database), 1, file);
    fclose(file);
}

void load_database(Database* db, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Could not open file!\n");
        return;
    }
    
    fread(db, sizeof(Database), 1, file);
    fclose(file);
}
```
- Serializes entire database to binary file
- Deserializes database from binary file
- Simple but effective persistence mechanism

### Display Functions
```c
void print_table_schema(Table* table) {
    printf("\nTable: %s\n", table->name);
    printf("Fields (%d):\n", table->field_count);
    for (int i = 0; i < table->field_count; i++) {
        printf("  %d. %s (%s)\n", i, table->fields[i].name,
               table->fields[i].type == 0 ? "string" : "integer");
    }
    printf("Records: %d\n", table->record_count);
    printf("Indexed field: %s\n", 
           table->indexed_field >= 0 ? table->fields[table->indexed_field].name : "None");
}

void print_records(Table* table) {
    printf("\nRecords in table '%s':\n", table->name);
    printf("ID");
    for (int i = 0; i < table->field_count; i++) {
        printf("\t%s", table->fields[i].name);
    }
    printf("\n");
    
    for (int i = 0; i < MAX_RECORDS; i++) {
        Record* record = &table->records[i];
        if (record->id == i) {  // Valid record
            printf("%d", record->id);
            for (int j = 0; j < table->field_count; j++) {
                printf("\t%s", record->values[j]);
            }
            printf("\n");
        }
    }
}
```
- Displays table schema and metadata
- Prints all records in tabular format
- Shows indexed field information

## Memory Management
- Uses fixed-size arrays for predictable memory usage
- Implements free list for efficient record allocation
- Avoids dynamic memory allocation complexity
- Binary serialization for persistence

## Indexing Implementation
- Simplified B+ tree concept using linear search
- Automatic index updates during insertions
- Key-based record lookups
- Support for single-field indexes

## Program Flow
1. Initialize database and data structures
2. Present menu for database operations
3. Handle user input and execute operations
4. Manage tables, fields, records, and indexes
5. Provide persistence through save/load operations
6. Continue until user exits

## Learning Points
1. **Database Fundamentals**: Tables, records, fields, and schemas
2. **Indexing Concepts**: B+ tree implementation and usage
3. **Memory Management**: Fixed-size arrays and free lists
4. **Data Structures**: Design for database entities
5. **File I/O**: Binary serialization and persistence
6. **CRUD Operations**: Create, read, update, delete functionality

## Limitations and Possible Improvements
1. **Fixed Memory Size**: Limited by predefined array sizes
2. **Simple Indexing**: Linear search instead of true B+ tree
3. **No Transactions**: No ACID properties or rollback mechanisms
4. **Limited Querying**: Only primary key and index-based lookups
5. **No Relationships**: No foreign key or join support
6. **Basic Types**: Only string and integer field types
7. **No Concurrency**: No multi-user or locking mechanisms