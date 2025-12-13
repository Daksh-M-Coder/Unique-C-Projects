# Spreadsheet Engine - Code Explanation

This document provides a detailed explanation of the implementation of the Spreadsheet Engine project.

## Data Structures

### Cell
Represents a single cell in the spreadsheet with multiple attributes:

```c
typedef struct {
    char value[MAX_CELL_LEN];      // Display value
    char formula[MAX_FORMULA_LEN]; // Original formula
    double numeric_value;          // Computed numeric value
    int is_formula;                // Flag indicating if cell contains formula
} Cell;
```

Each cell stores:
- The display value shown to the user
- The original formula entered by the user
- The computed numeric value for calculations
- A flag indicating whether the cell contains a formula

### Spreadsheet Grid
A 2D array of cells representing the entire spreadsheet:

```c
Cell spreadsheet[MAX_ROWS][MAX_COLS];
```

The grid is sized to accommodate 100 rows and 26 columns (A-Z).

### Token
Represents a lexical token during formula parsing:

```c
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_CELL_REF,
    TOKEN_FUNCTION,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_CELL_LEN];
    double number;
} Token;
```

Tokens are the basic units identified during lexical analysis of formulas.

## Core Functions

### Spreadsheet Management

#### init_spreadsheet()
Initializes all cells in the spreadsheet to empty values with default settings.

#### display_spreadsheet()
Renders the current state of the spreadsheet to the console in a tabular format.

#### set_cell()
Sets the value of a specific cell, handling both direct values and formulas. For formulas, it triggers evaluation.

### Formula Parsing and Evaluation

#### evaluate_formula()
The main entry point for formula evaluation. It takes a formula string and returns the computed result.

#### get_next_token()
Performs lexical analysis on the formula string, breaking it into tokens such as numbers, operators, and cell references.

#### parse_expression(), parse_term(), parse_factor()
Implement a recursive descent parser for arithmetic expressions with proper operator precedence:
- `parse_expression()` handles addition and subtraction (lowest precedence)
- `parse_term()` handles multiplication and division (medium precedence)
- `parse_factor()` handles numbers, cell references, and parenthesized expressions (highest precedence)

#### parse_cell_reference()
Converts cell references like "A1" or "B10" into row/column indices for accessing cell values.

### User Interface

#### print_menu()
Displays the main menu options to the user.

#### main()
The main function orchestrates the entire application, presenting a menu-driven interface and handling user interactions.

## Formula Evaluation Process

### Lexical Analysis
The formula string is first broken down into tokens:
1. Numbers (123, 3.14)
2. Operators (+, -, *, /)
3. Cell references (A1, B2)
4. Parentheses
5. End-of-formula marker

### Syntactic Analysis
Using recursive descent parsing, the token stream is analyzed according to grammar rules:
```
expression := term (('+' | '-') term)*
term := factor (('*' | '/') factor)*
factor := number | cell_reference | '(' expression ')'
```

### Semantic Evaluation
As the parser traverses the syntax tree, it computes actual values:
- Numbers are converted to double values
- Cell references retrieve values from the spreadsheet grid
- Arithmetic operations are performed with proper precedence

## Error Handling

The implementation includes error handling for several conditions:
- Invalid cell references (e.g., "1A", "ZZ1")
- Division by zero
- Malformed formulas (missing operands, unmatched parentheses)
- Out-of-bounds cell access

Errors are propagated through an error flag mechanism, allowing the system to gracefully handle invalid inputs.

## Memory Management

The implementation uses static allocation for all data structures:
- Fixed-size grid for the spreadsheet
- Fixed-length buffers for cell values and formulas
- Stack allocation for temporary variables

This approach simplifies memory management but limits flexibility.

## Design Patterns

### Visitor Pattern (Implicit)
The recursive descent parser implicitly uses a visitor-like approach where each parsing function "visits" a specific part of the syntax tree.

### State Machine
The main application loop implements a simple state machine with menu-driven states.

## Performance Considerations

1. **Direct Grid Access**: Cells are accessed directly via array indexing for O(1) access time
2. **Static Allocation**: Eliminates dynamic memory allocation overhead
3. **Simple Parsing**: Recursive descent parsing is efficient for simple grammars
4. **Limited Scope**: Constraints on grid size and formula complexity help maintain performance

## Limitations and Potential Improvements

### Current Limitations
1. **No Built-in Functions**: SUM, AVG, etc. are not supported
2. **Limited Data Types**: Only numbers and text strings
3. **No Persistence**: Spreadsheets cannot be saved or loaded
4. **Basic UI**: Simple console interface with limited interactivity

### Possible Enhancements
1. **Function Library**: Implement common spreadsheet functions
2. **File I/O**: Add save/load capabilities using CSV or custom formats
3. **Advanced Formatting**: Support for cell formatting and styling
4. **Graphical Interface**: Implement a GUI using a library like GTK or SDL
5. **Undo/Redo**: Add command history for reverting changes
6. **Copy/Paste**: Implement clipboard functionality
7. **Larger Grids**: Dynamic allocation for larger spreadsheets
8. **Performance Optimization**: Implement calculation caching and dependency tracking

## Learning Outcomes

This project demonstrates:
- Implementation of a recursive descent parser
- Data structure design for grid-based applications
- Error handling in interactive applications
- String parsing and manipulation techniques
- Menu-driven user interface design
- Separation of concerns in software architecture
- Memory management strategies