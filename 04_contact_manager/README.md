# Contact Management System

## Description
A console-based contact management system that allows users to store, view, search, and delete contact information. The system stores contacts in memory and persists data to a binary file between sessions. Each contact includes an ID, name, phone number, and email address.

## Features
- Add new contacts with name, phone number, and email
- View all stored contacts
- Search for contacts by name (partial matching supported)
- Delete contacts by ID
- Persistent storage using binary file I/O
- Automatic loading and saving of contacts
- Data validation and error handling

## Data Structure
The system uses a structure to represent contacts:
```c
typedef struct {
    int id;
    char name[50];
    char phone[15];
    char email[50];
} Contact;
```

## Standard Library Functions Used
- `stdio.h` - For input/output operations and file handling (`printf`, `scanf`, `fopen`, `fclose`, `fread`, `fwrite`)
- `stdlib.h` - For program termination (`exit`)
- `string.h` - For string operations (`strstr`)

## How to Compile and Run

### Compilation
```bash
gcc -o contact_manager main.c
```

### Execution
```bash
./contact_manager
```

On Windows:
```bash
contact_manager.exe
```

## How to Use
1. Run the program
2. Select an operation from the menu:
   - Add Contact: Enter contact details when prompted
   - View All Contacts: Display all stored contacts
   - Search Contact: Find contacts by name (supports partial matching)
   - Delete Contact: Remove a contact by entering its ID
   - Exit: Save contacts to file and exit the program
3. Choose to continue or exit after each operation

## Sample Output
```
Welcome to the Contact Management System!

===== Contact Management System =====
1. Add Contact
2. View All Contacts
3. Search Contact
4. Delete Contact
5. Exit
====================================
Enter your choice: 1
Enter name: John Doe
Enter phone number: 123-456-7890
Enter email: john.doe@example.com
Contact added successfully!

Do you want to perform another operation? (y/n): y

===== Contact Management System =====
1. Add Contact
2. View All Contacts
3. Search Contact
4. Delete Contact
5. Exit
====================================
Enter your choice: 2

===== All Contacts =====
ID: 1
Name: John Doe
Phone: 123-456-7890
Email: john.doe@example.com
------------------------
```

## Data Persistence
The system automatically saves contacts to a file named `contacts.dat` when exiting and loads them when starting. This binary file stores:
- The number of contacts
- All contact records

The file is created in the same directory as the executable.

## Limitations
1. Maximum of 100 contacts can be stored
2. Name, phone, and email fields have fixed length limits
3. No edit/update functionality for existing contacts
4. Phone and email formats are not validated