#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 1000
#define NAME_LENGTH 50

// Structure to represent a bank account
typedef struct {
    int accountNumber;
    char name[NAME_LENGTH];
    float balance;
} Account;

// Global array to store accounts
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function prototypes
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void transfer();
void saveAccountsToFile();
void loadAccountsFromFile();
void printMenu();

int main() {
    int choice;
    char continueOperation;

    // Load accounts from file if it exists
    loadAccountsFromFile();

    printf("Welcome to the Simple Banking System!\n");

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Create account
                createAccount();
                break;

            case 2: // Deposit money
                deposit();
                break;

            case 3: // Withdraw money
                withdraw();
                break;

            case 4: // Check balance
                checkBalance();
                break;

            case 5: // Transfer money
                transfer();
                break;

            case 6: // Exit
                saveAccountsToFile();
                printf("Accounts saved to file. Thank you for using the Simple Banking System!\n");
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

// Function to create a new account
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts. Maximum limit reached!\n");
        return;
    }

    Account newAccount;
    
    // Generate account number (simple approach: use accountCount + 1000)
    newAccount.accountNumber = 1000 + accountCount + 1;
    
    printf("Enter account holder name: ");
    scanf(" %[^\n]", newAccount.name);
    
    printf("Enter initial deposit amount: $");
    scanf("%f", &newAccount.balance);
    
    // Validate initial deposit
    if (newAccount.balance < 0) {
        printf("Initial deposit cannot be negative!\n");
        return;
    }

    accounts[accountCount] = newAccount;
    accountCount++;

    printf("Account created successfully!\n");
    printf("Account Number: %d\n", newAccount.accountNumber);
    printf("Account Holder: %s\n", newAccount.name);
    printf("Balance: $%.2f\n", newAccount.balance);
}

// Function to deposit money into an account
void deposit() {
    if (accountCount == 0) {
        printf("No accounts found!\n");
        return;
    }

    int accountNumber;
    float amount;
    
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    
    // Find account
    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("Enter deposit amount: $");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Deposit amount must be positive!\n");
        return;
    }
    
    accounts[index].balance += amount;
    printf("Deposit successful!\n");
    printf("New Balance: $%.2f\n", accounts[index].balance);
}

// Function to withdraw money from an account
void withdraw() {
    if (accountCount == 0) {
        printf("No accounts found!\n");
        return;
    }

    int accountNumber;
    float amount;
    
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    
    // Find account
    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("Enter withdrawal amount: $");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Withdrawal amount must be positive!\n");
        return;
    }
    
    if (amount > accounts[index].balance) {
        printf("Insufficient funds! Current balance: $%.2f\n", accounts[index].balance);
        return;
    }
    
    accounts[index].balance -= amount;
    printf("Withdrawal successful!\n");
    printf("New Balance: $%.2f\n", accounts[index].balance);
}

// Function to check account balance
void checkBalance() {
    if (accountCount == 0) {
        printf("No accounts found!\n");
        return;
    }

    int accountNumber;
    
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    
    // Find account
    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("\n===== Account Details =====\n");
    printf("Account Number: %d\n", accounts[index].accountNumber);
    printf("Account Holder: %s\n", accounts[index].name);
    printf("Current Balance: $%.2f\n", accounts[index].balance);
}

// Function to transfer money between accounts
void transfer() {
    if (accountCount < 2) {
        printf("At least two accounts are required for transfer!\n");
        return;
    }

    int fromAccount, toAccount;
    float amount;
    
    printf("Enter sender's account number: ");
    scanf("%d", &fromAccount);
    
    printf("Enter receiver's account number: ");
    scanf("%d", &toAccount);
    
    // Check if accounts are the same
    if (fromAccount == toAccount) {
        printf("Sender and receiver accounts cannot be the same!\n");
        return;
    }
    
    // Find sender account
    int fromIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == fromAccount) {
            fromIndex = i;
            break;
        }
    }
    
    if (fromIndex == -1) {
        printf("Sender account not found!\n");
        return;
    }
    
    // Find receiver account
    int toIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == toAccount) {
            toIndex = i;
            break;
        }
    }
    
    if (toIndex == -1) {
        printf("Receiver account not found!\n");
        return;
    }
    
    printf("Enter transfer amount: $");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("Transfer amount must be positive!\n");
        return;
    }
    
    if (amount > accounts[fromIndex].balance) {
        printf("Insufficient funds in sender's account! Current balance: $%.2f\n", 
               accounts[fromIndex].balance);
        return;
    }
    
    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;
    
    printf("Transfer successful!\n");
    printf("Sender's New Balance: $%.2f\n", accounts[fromIndex].balance);
    printf("Receiver's New Balance: $%.2f\n", accounts[toIndex].balance);
}

// Function to save accounts to a file
void saveAccountsToFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not save accounts to file!\n");
        return;
    }

    fwrite(&accountCount, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}

// Function to load accounts from a file
void loadAccountsFromFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        // File doesn't exist, which is fine for first run
        return;
    }

    fread(&accountCount, sizeof(int), 1, file);
    fread(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}

// Function to print the menu
void printMenu() {
    printf("\n===== Simple Banking System =====\n");
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Transfer Money\n");
    printf("6. Exit\n");
    printf("================================\n");
}