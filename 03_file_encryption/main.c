#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 123  // Simple XOR key for encryption/decryption

// Function prototypes
void encryptDecrypt(char *inputFile, char *outputFile);
void printMenu();

int main() {
    int choice;
    char inputFile[100], outputFile[100];
    char continueOperation;

    printf("Welcome to the File Encryption/Decryption Tool!\n");
    printf("This tool uses XOR encryption with a fixed key.\n");

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Encrypt file
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output file name: ");
                scanf("%s", outputFile);
                encryptDecrypt(inputFile, outputFile);
                printf("File encrypted successfully!\n");
                break;

            case 2: // Decrypt file
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output file name: ");
                scanf("%s", outputFile);
                encryptDecrypt(inputFile, outputFile);
                printf("File decrypted successfully!\n");
                break;

            case 3: // Exit
                printf("Thank you for using the File Encryption/Decryption Tool!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &continueOperation);
        printf("\n");

    } while (continueOperation == 'y' || continueOperation == 'Y');

    return 0;
}

// Function to encrypt or decrypt a file using XOR
void encryptDecrypt(char *inputFile, char *outputFile) {
    FILE *inFile, *outFile;
    char ch;

    // Open input file for reading
    inFile = fopen(inputFile, "rb");
    if (inFile == NULL) {
        printf("Error: Could not open input file '%s'\n", inputFile);
        return;
    }

    // Open output file for writing
    outFile = fopen(outputFile, "wb");
    if (outFile == NULL) {
        printf("Error: Could not create output file '%s'\n", outputFile);
        fclose(inFile);
        return;
    }

    // Read each byte from input file, XOR it with key, and write to output file
    while (fread(&ch, sizeof(char), 1, inFile) == 1) {
        ch ^= KEY;  // XOR operation
        fwrite(&ch, sizeof(char), 1, outFile);
    }

    // Close files
    fclose(inFile);
    fclose(outFile);
}

void printMenu() {
    printf("\n===== File Encryption/Decryption Tool =====\n");
    printf("1. Encrypt a file\n");
    printf("2. Decrypt a file\n");
    printf("3. Exit\n");
    printf("==========================================\n");
}