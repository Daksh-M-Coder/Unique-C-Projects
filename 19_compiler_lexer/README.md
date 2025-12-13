# Compiler Lexer

A lexical analyzer (tokenizer) for a subset of the C programming language.

## Description

This project implements a lexer that can tokenize C source code, identifying keywords, identifiers, numbers, strings, operators, and separators. Lexical analysis is the first phase of compilation, where the source code is broken down into tokens that can be processed by subsequent phases of the compiler.

## Features

- Tokenization of C source code
- Recognition of C keywords (int, if, for, while, etc.)
- Identification of identifiers and variables
- Parsing of numeric literals (integers and floating-point)
- String literal recognition
- Operator detection (+, -, *, /, ==, !=, etc.)
- Separator identification (parentheses, braces, semicolons, etc.)
- Comment handling (both single-line and multi-line)
- Position tracking (line and column numbers)
- Error reporting for unknown tokens

## Compilation

To compile this project, use the following command:

```bash
gcc -o lexer main.c
```

## Usage

Run the program with:

```bash
./lexer
```

The program will first tokenize a sample C program and display the results. Then it will enter interactive mode where you can input your own C code to tokenize.

To exit the interactive mode, press Ctrl+C.

## Supported Token Types

1. **Keywords**: Reserved words in C (int, if, for, while, return, etc.)
2. **Identifiers**: Variable and function names
3. **Numbers**: Integer and floating-point literals
4. **Strings**: String literals enclosed in double quotes
5. **Operators**: Arithmetic, relational, and logical operators
6. **Separators**: Punctuation marks (parentheses, braces, semicolons, commas)
7. **Comments**: Both single-line (//) and multi-line (/* */) comments

## Technical Details

### Token Structure

Each token contains:
- Type: The category of the token
- Value: The actual text of the token
- Line: The line number where the token appears
- Column: The column number where the token starts

### Lexical Analysis Process

1. **Whitespace Skipping**: Skip spaces, tabs, and newlines
2. **Comment Handling**: Identify and process comments
3. **String Literals**: Recognize quoted strings
4. **Multi-character Operators**: Detect operators like ++, ==, <=
5. **Single-character Tokens**: Identify single-character operators and separators
6. **Identifiers/Keywords**: Parse alphanumeric sequences
7. **Numbers**: Recognize numeric literals
8. **Error Handling**: Report unknown characters

### Implementation Approach

The lexer uses a sequential scanning approach:
1. Scan the input character by character
2. Identify the beginning of the next token
3. Accumulate characters until the token is complete
4. Classify the token based on its content
5. Return the token with position information

## Supported C Language Subset

The lexer supports a substantial subset of C including:
- All C keywords
- Identifiers with letters, digits, and underscores
- Decimal integers and floating-point numbers
- String literals with escape sequences
- All common C operators
- Standard C separators
- Both C-style comments

## Limitations

This is an educational implementation with some limitations:
- No support for character literals ('a')
- No support for preprocessor directives (#include, #define)
- No handling of escape sequences in strings
- No validation of identifier naming rules
- No support for hexadecimal or octal literals
- Simplified error handling

## Possible Extensions

- Add support for character literals
- Implement preprocessor directive handling
- Add escape sequence processing in strings
- Support for hexadecimal and octal number literals
- Enhanced error reporting with detailed diagnostics
- Unicode support for identifiers
- Integration with a parser for a complete compiler front-end
- Visualization of the token stream

## Requirements

- Standard C library

## License

This project is released into the public domain.