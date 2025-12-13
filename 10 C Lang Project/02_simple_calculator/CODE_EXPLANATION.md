# Simple Calculator - Code Explanation

## Program Structure
The calculator program follows a modular approach with separate functions for each mathematical operation and a main control loop that handles user interaction. The program uses a menu-driven interface to allow users to select operations.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
```
- `stdio.h`: Provides input/output functions like `printf()` and `scanf()`
- `stdlib.h`: Contains the `exit()` function for program termination
- `math.h`: Provides mathematical functions like `pow()` and `sqrt()`

### Function Prototypes
```c
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double power(double a, double b);
double square_root(double a);
void print_menu();
```
These declarations inform the compiler about functions that will be defined later in the code, allowing them to be used before their actual definition.

### Variables
```c
int choice;
double num1, num2, result;
char continue_calc;
```
- `choice`: Stores the user's menu selection
- `num1`, `num2`: Store the operands for calculations
- `result`: Stores the result of calculations
- `continue_calc`: Stores the user's choice to continue or exit

### Main Function Structure
The main function implements a `do-while` loop that continues until the user chooses to exit:
1. Display menu
2. Get user choice
3. Process choice with a `switch` statement
4. Ask if user wants to continue

### Switch Statement for Operation Selection
The `switch` statement handles different operations based on user input:
- Cases 1-6 correspond to different mathematical operations
- Case 7 exits the program
- Default case handles invalid input

### Mathematical Operations
Each operation is implemented as a separate function:
- `add()`, `subtract()`, `multiply()`, `divide()`: Basic arithmetic
- `power()`: Uses `pow()` from math.h
- `square_root()`: Uses `sqrt()` from math.h

### Error Handling
The program includes error checking for critical operations:
- Division by zero check in the divide function
- Negative number check for square root calculation

### Input/Output Handling
```c
scanf("%lf %lf", &num1, &num2);  // For two floating-point numbers
scanf("%lf", &num1);             // For single floating-point number
scanf(" %c", &continue_calc);    // For character input (note space)
```
- `%lf` is used for double precision floating-point numbers
- Space before `%c` consumes any leftover newline characters

## Program Flow
1. Welcome message is displayed
2. Main loop begins:
   - Menu is printed
   - User selects an operation
   - Program gets required inputs
   - Selected operation is performed
   - Result is displayed
   - Error checking is performed where necessary
   - User is asked if they want to continue
3. Loop continues until user chooses to exit

## Learning Points
1. **Modular Programming**: Breaking code into separate functions for each operation
2. **Switch Statements**: Efficient way to handle multiple choices
3. **Math Library Usage**: Incorporating mathematical functions from math.h
4. **Error Handling**: Checking for invalid operations like division by zero
5. **Function Prototypes**: Declaring functions before main for better code organization
6. **Data Types**: Using appropriate data types (double for precision)
7. **Input Validation**: Handling different types of user input correctly