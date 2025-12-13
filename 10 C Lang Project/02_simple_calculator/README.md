# Simple Calculator

## Description
A command-line calculator that performs basic arithmetic operations including addition, subtraction, multiplication, division, exponentiation, and square root calculations. The calculator features a menu-driven interface and error handling for invalid operations.

## Features
- Addition, subtraction, multiplication, and division operations
- Exponentiation (power) calculations
- Square root calculations
- Error handling for division by zero
- Error handling for square root of negative numbers
- Menu-driven interface
- Continuous operation until user chooses to exit

## Standard Library Functions Used
- `stdio.h` - For input/output operations (`printf`, `scanf`)
- `stdlib.h` - For program termination (`exit`)
- `math.h` - For mathematical functions (`pow`, `sqrt`)

## How to Compile and Run

### Compilation
```bash
gcc -o calculator main.c -lm
```
Note: The `-lm` flag is required to link the math library on most systems.

### Execution
```bash
./calculator
```

On Windows:
```bash
calculator.exe
```

## How to Use
1. Run the program
2. Select an operation from the menu (1-7)
3. Enter the required numbers when prompted
4. View the result
5. Choose to continue or exit

## Sample Output
```
Welcome to the Simple Calculator!

===== Simple Calculator =====
1. Addition (+)
2. Subtraction (-)
3. Multiplication (*)
4. Division (/)
5. Power (^)
6. Square Root (√)
7. Exit
=============================
Enter your choice: 1
Enter two numbers: 10 5
10.00 + 5.00 = 15.00

Do you want to continue? (y/n): y

===== Simple Calculator =====
1. Addition (+)
2. Subtraction (-)
3. Multiplication (*)
4. Division (/)
5. Power (^)
6. Square Root (√)
7. Exit
=============================
Enter your choice: 4
Enter two numbers: 10 3
10.00 / 3.00 = 3.33

Do you want to continue? (y/n): n
```