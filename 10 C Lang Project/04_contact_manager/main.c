#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 15
#define EMAIL_LENGTH 50

// Structure to represent a contact
typedef struct {
    int id;
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
} Contact;

// Global array to store contacts
Contact contacts[MAX_CONTACTS];
int contactCount = 0;

// Function prototypes
void addContact();
void viewContacts();
void searchContact();
void deleteContact();
void saveContactsToFile();
void loadContactsFromFile();
void printMenu();

int main() {
    int choice;
    char continueOperation;

    // Load contacts from file if it exists
    loadContactsFromFile();

    printf("Welcome to the Contact Management System!\n");

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add contact
                addContact();
                break;

            case 2: // View all contacts
                viewContacts();
                break;

            case 3: // Search contact
                searchContact();
                break;

            case 4: // Delete contact
                deleteContact();
                break;

            case 5: // Exit
                saveContactsToFile();
                printf("Contacts saved to file. Thank you for using the Contact Management System!\n");
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

// Function to add a new contact
void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("Cannot add more contacts. Maximum limit reached!\n");
        return;
    }

    Contact newContact;
    newContact.id = contactCount + 1;

    printf("Enter name: ");
    scanf(" %[^\n]", newContact.name);  // Read string with spaces
    
    printf("Enter phone number: ");
    scanf(" %[^\n]", newContact.phone);
    
    printf("Enter email: ");
    scanf(" %[^\n]", newContact.email);

    contacts[contactCount] = newContact;
    contactCount++;

    printf("Contact added successfully!\n");
}

// Function to view all contacts
void viewContacts() {
    if (contactCount == 0) {
        printf("No contacts found!\n");
        return;
    }

    printf("\n===== All Contacts =====\n");
    for (int i = 0; i < contactCount; i++) {
        printf("ID: %d\n", contacts[i].id);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
        printf("------------------------\n");
    }
}

// Function to search for a contact by name
void searchContact() {
    if (contactCount == 0) {
        printf("No contacts found!\n");
        return;
    }

    char searchName[NAME_LENGTH];
    int found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < contactCount; i++) {
        if (strstr(contacts[i].name, searchName) != NULL) {
            printf("\n===== Contact Found =====\n");
            printf("ID: %d\n", contacts[i].id);
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Email: %s\n", contacts[i].email);
            printf("------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No contact found with name '%s'\n", searchName);
    }
}

// Function to delete a contact by ID
void deleteContact() {
    if (contactCount == 0) {
        printf("No contacts found!\n");
        return;
    }

    int id, found = 0;
    printf("Enter contact ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].id == id) {
            // Shift all contacts after this one position to the left
            for (int j = i; j < contactCount - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            contactCount--;
            found = 1;
            printf("Contact deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Contact with ID %d not found!\n", id);
    }
}

// Function to save contacts to a file
void saveContactsToFile() {
    FILE *file = fopen("contacts.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not save contacts to file!\n");
        return;
    }

    fwrite(&contactCount, sizeof(int), 1, file);
    fwrite(contacts, sizeof(Contact), contactCount, file);
    fclose(file);
}

// Function to load contacts from a file
void loadContactsFromFile() {
    FILE *file = fopen("contacts.dat", "rb");
    if (file == NULL) {
        // File doesn't exist, which is fine for first run
        return;
    }

    fread(&contactCount, sizeof(int), 1, file);
    fread(contacts, sizeof(Contact), contactCount, file);
    fclose(file);
}

// Function to print the menu
void printMenu() {
    printf("\n===== Contact Management System =====\n");
    printf("1. Add Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contact\n");
    printf("4. Delete Contact\n");
    printf("5. Exit\n");
    printf("====================================\n");
}