# Simple Banking System

## Description
A console-based banking system that simulates basic banking operations including account creation, deposits, withdrawals, balance inquiries, and fund transfers. The system stores account information in memory and persists data to a binary file between sessions.

## Features
- Create new bank accounts with account holder names
- Deposit money into accounts
- Withdraw money from accounts (with balance validation)
- Check account balances
- Transfer money between accounts (with validation)
- Persistent storage using binary file I/O
- Automatic loading and saving of accounts
- Data validation and error handling

## Data Structure
The system uses a structure to represent bank accounts:
```c
typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;
```

## Standard Library Functions Used
- `stdio.h` - For input/output operations and file handling (`printf`, `scanf`, `fopen`, `fclose`, `fread`, `fwrite`)
- `stdlib.h` - For program termination (`exit`)
- `string.h` - For string operations (`strcpy`)

## How to Compile and Run

### Compilation
```bash
gcc -o banking_system main.c
```

### Execution
```bash
./banking_system
```

On Windows:
```bash
banking_system.exe
```

## How to Use
1. Run the program
2. Select an operation from the menu:
   - Create Account: Enter account holder name and initial deposit
   - Deposit Money: Add funds to an existing account
   - Withdraw Money: Remove funds from an account (subject to balance)
   - Check Balance: View current account balance
   - Transfer Money: Move funds between two accounts
   - Exit: Save accounts to file and exit the program
3. Choose to continue or exit after each operation

## Sample Output
```
Welcome to the Simple Banking System!

===== Simple Banking System =====
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Transfer Money
6. Exit
================================
Enter your choice: 1
Enter account holder name: John Doe
Enter initial deposit amount: $1000
Account created successfully!
Account Number: 1001
Account Holder: John Doe
Balance: $1000.00

Do you want to perform another operation? (y/n): y

===== Simple Banking System =====
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Transfer Money
6. Exit
================================
Enter your choice: 4
Enter account number: 1001

===== Account Details =====
Account Number: 1001
Account Holder: John Doe
Current Balance: $1000.00
```

## Account Number Generation
Account numbers are automatically generated starting from 1001 and incrementing for each new account.

## Data Persistence
The system automatically saves accounts to a file named `accounts.dat` when exiting and loads them when starting. This binary file stores:
- The number of accounts
- All account records

The file is created in the same directory as the executable.

## Security Notes
This is a simplified banking system for educational purposes and lacks many security features of real banking systems:
- No password protection
- No encryption of account data
- No transaction logging
- No audit trails
- No concurrent access controls

## Limitations
1. Maximum of 1000 accounts can be stored
2. Account holder names have a fixed length limit of 50 characters
3. No account deletion functionality
4. No interest calculation
5. No account statement generation