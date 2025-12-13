# Mathematical Expression Evaluator

## Description
A mathematical expression evaluator that parses and computes arithmetic expressions using recursive descent parsing. The program supports basic operations (+, -, *, /), exponentiation (^), parentheses for grouping, and floating-point numbers. It implements a proper tokenizer and parser with operator precedence handling.

## Features
- Recursive descent parsing for mathematical expressions
- Support for basic arithmetic operations (+, -, *, /)
- Exponentiation operator (^) with right associativity
- Parentheses for expression grouping
- Floating-point number support
- Operator precedence handling
- Error detection and reporting
- Interactive command-line interface

## Parsing Technique
The evaluator uses recursive descent parsing, a top-down parsing technique that implements one function for each grammar rule. The parser follows standard mathematical operator precedence:
1. Parentheses (highest precedence)
2. Unary plus and minus
3. Exponentiation (right associative)
4. Multiplication and division
5. Addition and subtraction (lowest precedence)

## Standard Library Functions Used
- `stdio.h` - For input/output operations
- `stdlib.h` - For standard library functions like `strtod`
- `string.h` - For string manipulation functions
- `ctype.h` - For character classification functions
- `math.h` - For mathematical functions like `pow`

## How to Compile and Run

### Compilation
```bash
gcc -o evaluator main.c -lm
```
Note: The `-lm` flag is required to link the math library.

### Execution
```bash
./evaluator
```

On Windows:
```bash
evaluator.exe
```

## How to Use
1. Run the program
2. Enter mathematical expressions when prompted
3. Supported operations:
   - Addition: `+`
   - Subtraction: `-`
   - Multiplication: `*`
   - Division: `/`
   - Exponentiation: `^`
   - Parentheses: `()`
4. Type 'quit' or 'exit' to terminate the program

## Sample Usage
```
Mathematical Expression Evaluator
Supported operations: +, -, *, /, ^ (power), parentheses
Type 'quit' to exit

Enter expression: 2 + 3 * 4
Result: 14.000000

Enter expression: (2 + 3) * 4
Result: 20.000000

Enter expression: 2^3^2
Result: 512.000000

Enter expression: -5 + 3
Result: -2.000000

Enter expression: 10 / (2 + 3)
Result: 2.000000
```

## Grammar Implemented
The parser implements the following grammar:
```
expression → term (('+' | '-') term)*
term → factor (('*' | '/') factor)*
factor → power ('^' factor)?
power → ('-' | '+')? primary
primary → NUMBER | '(' expression ')'
```

## Educational Value
This implementation demonstrates:
1. Recursive descent parsing technique
2. Operator precedence handling
3. Tokenization of input strings
4. Context-free grammar implementation
5. Error handling in parsers
6. Mathematical expression evaluation
7. Associativity rules (left vs right)