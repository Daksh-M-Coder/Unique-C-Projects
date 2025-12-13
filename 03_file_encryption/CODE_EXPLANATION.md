# File Encryption/Decryption Tool - Code Explanation

## Program Structure
The program implements a menu-driven interface for file encryption and decryption using XOR cipher. The same function handles both operations since XOR encryption is symmetric. The program uses binary file I/O to ensure it works with any type of file.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
- `stdio.h`: Provides file I/O functions (`fopen`, `fclose`, `fread`, `fwrite`) and standard I/O (`printf`, `scanf`)
- `stdlib.h`: Contains the `exit()` function for program termination
- `string.h`: Included for potential string operations (though not heavily used here)

### Preprocessor Directive
```c
#define KEY 123
```
Defines a constant key value (123) used for XOR encryption/decryption. This is a simple approach for demonstration purposes.

### Function Prototypes
```c
void encryptDecrypt(char *inputFile, char *outputFile);
void printMenu();
```
- `encryptDecrypt()`: Performs the actual encryption or decryption operation
- `printMenu()`: Displays the user interface menu

### Variables
```c
int choice;
char inputFile[100], outputFile[100];
char continueOperation;
```
- `choice`: Stores the user's menu selection
- `inputFile`, `outputFile`: Character arrays to store file names (with buffer size of 100)
- `continueOperation`: Stores user's choice to continue or exit

### XOR Encryption/Decryption Function
The core of the program is the `encryptDecrypt()` function:
```c
void encryptDecrypt(char *inputFile, char *outputFile) {
    FILE *inFile, *outFile;
    char ch;
    
    // File opening and error checking
    inFile = fopen(inputFile, "rb");
    outFile = fopen(outputFile, "wb");
    
    // XOR operation
    while (fread(&ch, sizeof(char), 1, inFile) == 1) {
        ch ^= KEY;
        fwrite(&ch, sizeof(char), 1, outFile);
    }
    
    // File closing
    fclose(inFile);
    fclose(outFile);
}
```

## Detailed Code Walkthrough

### File Operations
The program opens files in binary mode:
- `"rb"`: Read binary mode for input file
- `"wb"`: Write binary mode for output file

Binary mode ensures the program works with any file type, not just text files.

### XOR Cipher Implementation
```c
while (fread(&ch, sizeof(char), 1, inFile) == 1) {
    ch ^= KEY;
    fwrite(&ch, sizeof(char), 1, outFile);
}
```
This loop reads one byte at a time from the input file, applies XOR with the key, and writes the result to the output file. The XOR operation has the property that applying it twice with the same key returns the original value, making it perfect for symmetric encryption.

### Error Handling
The program includes basic error checking for file operations:
```c
if (inFile == NULL) {
    printf("Error: Could not open input file '%s'\n", inputFile);
    return;
}
```
If a file cannot be opened, the function prints an error message and returns early.

### Input/Output Handling
```c
scanf("%s", inputFile);        // For string input (file names)
scanf(" %c", &continueOperation); // For character input with space
```
- `%s` reads a string (file name) without spaces
- Space before `%c` consumes leftover newline characters

## Program Flow
1. Welcome message is displayed
2. Main loop begins:
   - Menu is printed
   - User selects an operation
   - Program gets input and output file names
   - `encryptDecrypt()` function is called
   - Success message is displayed
   - User is asked if they want to continue
3. Loop continues until user chooses to exit

## Learning Points
1. **File I/O Operations**: Opening, reading, writing, and closing files in binary mode
2. **Bitwise Operations**: Using XOR for encryption/decryption
3. **Symmetric Encryption**: Understanding how the same operation works for both encryption and decryption
4. **Error Handling**: Checking return values of file operations
5. **Buffer Management**: Using character arrays for string storage
6. **Binary vs Text Mode**: Understanding when to use binary file operations
7. **Function Reusability**: Using a single function for both encryption and decryption

## Limitations and Improvements
1. **Fixed Key**: Using a constant key is not secure; a more robust implementation would use a variable key
2. **No Authentication**: The tool doesn't verify if a file was actually encrypted with this tool
3. **Buffer Size**: Processing one byte at a time is inefficient; buffering would improve performance
4. **Key Security**: The key is hardcoded in the source, making it visible to anyone with access to the binary