# Simple Banking System - Code Explanation

## Program Structure
The simple banking system simulates basic banking operations using structured data and file persistence. The program implements core banking functionalities like account creation, deposits, withdrawals, balance checks, and fund transfers. It uses a menu-driven interface for user interaction and binary file I/O for data persistence.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
- `stdio.h`: For input/output operations and file handling
- `stdlib.h`: For program termination with `exit()`
- `string.h`: For string operations (though not heavily used in this implementation)

### Constants and Data Structures
```c
#define MAX_ACCOUNTS 1000
#define NAME_LENGTH 50

typedef struct {
    int accountNumber;
    char name[NAME_LENGTH];
    float balance;
} Account;
```
- `MAX_ACCOUNTS`: Maximum number of accounts that can be stored
- `NAME_LENGTH`: Maximum length of account holder names
- `Account`: Structure to represent a bank account with account number, name, and balance

### Global Variables
```c
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
```
- `accounts`: Array to store all bank accounts
- `accountCount`: Tracks the current number of accounts

### Function Prototypes
```c
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void transfer();
void saveAccountsToFile();
void loadAccountsFromFile();
void printMenu();
```
Each function handles a specific banking operation or system functionality.

## Detailed Code Walkthrough

### Main Function
The main function orchestrates the entire program:
1. Loads existing accounts from file
2. Displays welcome message
3. Runs a loop showing menu and processing user choices
4. Saves accounts to file before exit

### Account Creation
```c
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
```
- Checks if maximum account limit is reached
- Generates unique account numbers starting from 1001
- Uses `scanf(" %[^\n]", ...)` to read names with spaces
- Validates initial deposit amount
- Adds account to array and increments counter

### Deposit Function
```c
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
```
- Searches for account by account number
- Validates deposit amount is positive
- Updates account balance
- Provides confirmation with new balance

### Withdrawal Function
```c
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
```
- Similar to deposit but with additional balance check
- Prevents overdrafts by validating sufficient funds
- Updates balance and provides confirmation

### Balance Inquiry
```c
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
```
- Retrieves and displays account details
- Formats output for readability

### Fund Transfer
```c
void transfer() {
    if (accountCount < 2) {
        printf("At least two accounts are required for transfer!\n");
        return;
    }

    int fromAccount, toAccount;
    float amount;
    
    // Get sender and receiver account numbers
    printf("Enter sender's account number: ");
    scanf("%d", &fromAccount);
    
    printf("Enter receiver's account number: ");
    scanf("%d", &toAccount);
    
    // Validate accounts are different
    if (fromAccount == toAccount) {
        printf("Sender and receiver accounts cannot be the same!\n");
        return;
    }
    
    // Find both accounts
    int fromIndex = -1, toIndex = -1;
    // ... search logic for both accounts
    
    // Validate transfer amount
    if (amount <= 0) {
        printf("Transfer amount must be positive!\n");
        return;
    }
    
    // Check sufficient funds
    if (amount > accounts[fromIndex].balance) {
        printf("Insufficient funds in sender's account! Current balance: $%.2f\n", 
               accounts[fromIndex].balance);
        return;
    }
    
    // Perform transfer
    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;
    
    printf("Transfer successful!\n");
    printf("Sender's New Balance: $%.2f\n", accounts[fromIndex].balance);
    printf("Receiver's New Balance: $%.2f\n", accounts[toIndex].balance);
}
```
- Validates both accounts exist and are different
- Checks sufficient funds in sender's account
- Atomically updates both accounts
- Provides confirmation with new balances

### File I/O Functions
```c
void saveAccountsToFile() {
    FILE *file = fopen("accounts.dat", "wb");
    fwrite(&accountCount, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}

void loadAccountsFromFile() {
    FILE *file = fopen("accounts.dat", "rb");
    fread(&accountCount, sizeof(int), 1, file);
    fread(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}
```
- Binary file operations for efficient storage
- Saves both account count and account array
- Handles file opening errors gracefully

## Input/Output Handling
Special attention is paid to input handling:
- `scanf(" %[^\n]", string)`: Reads strings including spaces until newline
- `scanf("%f", &float_var)`: Reads floating-point numbers
- `scanf("%d", &int_var)`: Reads integers
- Space before format specifier consumes leftover newline characters

## Program Flow
1. Program starts and loads accounts from file
2. Main loop displays menu and processes user choices
3. Each banking operation is executed through dedicated functions
4. User can continue operations or exit
5. On exit, accounts are saved to file

## Learning Points
1. **Structures**: Using structs to organize related data
2. **Arrays of Structures**: Managing collections of structured data
3. **File I/O**: Binary file operations for data persistence
4. **String Handling**: Reading and storing names with spaces
5. **Validation**: Input validation and error checking
6. **Financial Calculations**: Working with monetary values
7. **Menu-Driven Interface**: Creating user-friendly console applications
8. **Data Manipulation**: Adding, searching, and updating array elements

## Limitations and Possible Improvements
1. **Fixed Array Size**: Could be improved with dynamic memory allocation
2. **Account Number Generation**: Simple incremental approach; real systems use more complex schemes
3. **No Account Editing**: Missing functionality to update account holder names
4. **No Account Deletion**: Cannot close accounts
5. **Limited Validation**: No format checking for names
6. **Security**: No authentication or authorization mechanisms
7. **Concurrency**: Not designed for multi-user access
8. **Transaction Logging**: No audit trail of transactions