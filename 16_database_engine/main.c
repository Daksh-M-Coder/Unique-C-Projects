#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RECORDS 1000
#define MAX_FIELDS 10
#define MAX_FIELD_NAME 32
#define MAX_FIELD_VALUE 256
#define MAX_INDEX_ENTRIES 1000

// Field structure
typedef struct {
    char name[MAX_FIELD_NAME];
    int type;  // 0 = string, 1 = integer
} Field;

// Record structure
typedef struct {
    int id;
    char values[MAX_FIELDS][MAX_FIELD_VALUE];
    int next;  // For linked list of records
} Record;

// Index entry structure
typedef struct {
    char key[MAX_FIELD_VALUE];
    int record_id;
} IndexEntry;

// Table structure
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

// Database structure
typedef struct {
    Table tables[10];
    int table_count;
} Database;

// Function prototypes
void init_database(Database* db);
Table* create_table(Database* db, const char* name);
int add_field(Table* table, const char* name, int type);
int insert_record(Table* table, const char* values[]);
Record* find_record(Table* table, int id);
void create_index(Table* table, int field_index);
Record* find_by_index(Table* table, const char* key);
void print_table_schema(Table* table);
void print_records(Table* table);
void save_database(Database* db, const char* filename);
void load_database(Database* db, const char* filename);
void print_menu();

int main() {
    Database db;
    int choice, table_id, field_type;
    char table_name[32], field_name[32];
    char* values[MAX_FIELDS];
    char value_buffer[MAX_FIELDS][MAX_FIELD_VALUE];
    int record_id;
    char search_key[MAX_FIELD_VALUE];
    
    init_database(&db);
    
    printf("Simple Database Engine with B+ Tree Indexing\n");
    printf("Supports basic CRUD operations and indexing\n\n");
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Create table
                printf("Enter table name: ");
                scanf("%s", table_name);
                Table* table = create_table(&db, table_name);
                if (table) {
                    printf("Table '%s' created successfully!\n", table_name);
                } else {
                    printf("Failed to create table!\n");
                }
                break;
                
            case 2:  // Add field
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    printf("Enter field name: ");
                    scanf("%s", field_name);
                    printf("Enter field type (0=string, 1=integer): ");
                    scanf("%d", &field_type);
                    if (add_field(&db.tables[table_id], field_name, field_type)) {
                        printf("Field added successfully!\n");
                    } else {
                        printf("Failed to add field!\n");
                    }
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 3:  // Insert record
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    Table* t = &db.tables[table_id];
                    printf("Enter %d field values:\n", t->field_count);
                    for (int i = 0; i < t->field_count; i++) {
                        printf("  %s: ", t->fields[i].name);
                        scanf("%s", value_buffer[i]);
                        values[i] = value_buffer[i];
                    }
                    int id = insert_record(t, (const char**)values);
                    if (id >= 0) {
                        printf("Record inserted with ID %d\n", id);
                    } else {
                        printf("Failed to insert record!\n");
                    }
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 4:  // Find record
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    printf("Enter record ID: ");
                    scanf("%d", &record_id);
                    Record* record = find_record(&db.tables[table_id], record_id);
                    if (record) {
                        printf("Record found:\n");
                        for (int i = 0; i < db.tables[table_id].field_count; i++) {
                            printf("  %s: %s\n", 
                                   db.tables[table_id].fields[i].name,
                                   record->values[i]);
                        }
                    } else {
                        printf("Record not found!\n");
                    }
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 5:  // Create index
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    int field_index;
                    printf("Enter field index to index (0-%d): ", 
                           db.tables[table_id].field_count - 1);
                    scanf("%d", &field_index);
                    if (field_index >= 0 && field_index < db.tables[table_id].field_count) {
                        create_index(&db.tables[table_id], field_index);
                        printf("Index created on field '%s'!\n", 
                               db.tables[table_id].fields[field_index].name);
                    } else {
                        printf("Invalid field index!\n");
                    }
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 6:  // Search by index
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    printf("Enter search key: ");
                    scanf("%s", search_key);
                    Record* record = find_by_index(&db.tables[table_id], search_key);
                    if (record) {
                        printf("Record found via index:\n");
                        for (int i = 0; i < db.tables[table_id].field_count; i++) {
                            printf("  %s: %s\n", 
                                   db.tables[table_id].fields[i].name,
                                   record->values[i]);
                        }
                    } else {
                        printf("Record not found!\n");
                    }
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 7:  // Print table schema
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    print_table_schema(&db.tables[table_id]);
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 8:  // Print all records
                printf("Enter table ID (0-%d): ", db.table_count - 1);
                scanf("%d", &table_id);
                if (table_id >= 0 && table_id < db.table_count) {
                    print_records(&db.tables[table_id]);
                } else {
                    printf("Invalid table ID!\n");
                }
                break;
                
            case 9:  // Save database
                {
                    char filename[256];
                    printf("Enter filename to save: ");
                    scanf("%s", filename);
                    save_database(&db, filename);
                    printf("Database saved successfully!\n");
                }
                break;
                
            case 10:  // Load database
                {
                    char filename[256];
                    printf("Enter filename to load: ");
                    scanf("%s", filename);
                    load_database(&db, filename);
                    printf("Database loaded successfully!\n");
                }
                break;
                
            case 11:  // Exit
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

// Initialize database
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

// Create a new table
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

// Add field to table
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

// Insert record into table
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

// Find record by ID
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

// Create index on a field
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

// Find record by index key
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

// Print table schema
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

// Print all records
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

// Save database to file
void save_database(Database* db, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Could not create file!\n");
        return;
    }
    
    fwrite(db, sizeof(Database), 1, file);
    fclose(file);
}

// Load database from file
void load_database(Database* db, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Could not open file!\n");
        return;
    }
    
    fread(db, sizeof(Database), 1, file);
    fclose(file);
}

// Print menu
void print_menu() {
    printf("\n===== Database Engine =====\n");
    printf("1. Create table\n");
    printf("2. Add field to table\n");
    printf("3. Insert record\n");
    printf("4. Find record by ID\n");
    printf("5. Create index\n");
    printf("6. Search by index\n");
    printf("7. Print table schema\n");
    printf("8. Print all records\n");
    printf("9. Save database\n");
    printf("10. Load database\n");
    printf("11. Exit\n");
    printf("=========================\n");
}