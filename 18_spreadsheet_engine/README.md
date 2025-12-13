# Spreadsheet Engine

A simple spreadsheet application that supports basic formulas and cell references.

## Description

This project implements a basic spreadsheet engine that can store values in cells, evaluate formulas with cell references, and perform arithmetic operations. The spreadsheet supports a subset of features found in commercial spreadsheet applications like Microsoft Excel or Google Sheets.

## Features

- Grid-based spreadsheet with rows and columns (A-Z, 1-100)
- Cell value assignment with text or numbers
- Formula evaluation with basic arithmetic operations (+, -, *, /)
- Cell references in formulas (e.g., =A1+B2)
- Parentheses support for controlling operation precedence
- Error handling for invalid formulas and circular references
- Simple text-based user interface

## Compilation

To compile this project, use the following command:

```bash
gcc -o spreadsheet main.c -lm
```

Note: The `-lm` flag is required to link the math library.

## Usage

Run the program with:

```bash
./spreadsheet
```

The program presents a menu-driven interface:

1. Display spreadsheet - Shows the current state of the spreadsheet
2. Set cell value - Allows setting a value or formula in a specific cell
3. Quit - Exits the application

### Setting Cell Values

To set a cell value:
1. Choose option 2 from the menu
2. Enter the cell reference (e.g., A1, B2)
3. Enter the value or formula:
   - For text/numbers: Just enter the value (e.g., "Hello", "123")
   - For formulas: Start with "=" (e.g., "=A1+B1", "=A1*2")

## Supported Formula Syntax

- Basic arithmetic operations: +, -, *, /
- Cell references: A1, B2, C10, etc.
- Numbers: 123, 3.14, -5
- Parentheses for grouping: (A1+B1)*C1

## Technical Details

### Data Structures

- **Cell**: Represents a single cell with value, formula, and computed numeric value
- **Grid**: 2D array of cells representing the spreadsheet

### Formula Evaluation

The formula evaluation uses a recursive descent parser that implements:
1. Lexical analysis (tokenization)
2. Syntactic analysis (parsing)
3. Semantic evaluation (computation)

The parser supports operator precedence:
1. Parentheses (highest precedence)
2. Multiplication and division
3. Addition and subtraction (lowest precedence)

### Error Handling

The engine handles various error conditions:
- Invalid cell references
- Circular references (indirectly)
- Division by zero
- Malformed formulas
- Invalid operators

## Limitations

This is a simplified implementation with several limitations:
- No support for advanced functions (SUM, AVG, etc.)
- Limited to 26 columns (A-Z)
- No floating-point precision controls
- No saving/loading of spreadsheets to files
- No copy/paste functionality
- No formatting options

## Possible Extensions

- Add support for built-in functions (SUM, AVG, MIN, MAX)
- Implement saving/loading spreadsheets to/from files
- Add support for more data types (dates, currency)
- Implement undo/redo functionality
- Add cell formatting options
- Support for larger grids
- Graphing/charting capabilities
- Macro recording and playback

## Requirements

- Standard C library
- Math library (`libm`)

## License

This project is released into the public domain.