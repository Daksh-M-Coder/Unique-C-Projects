# Compiler Lexer - Code Explanation

This document provides a detailed explanation of the implementation of the Compiler Lexer project.

## Data Structures

### TokenType Enum
Defines the different categories of tokens that the lexer can recognize:

```c
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_SEPARATOR,
    TOKEN_COMMENT,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;
```

Each token type represents a distinct category of lexical elements in the C language.

### Token Structure
Represents a single token with its metadata:

```c
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
    int line;
    int column;
} Token;
```

Each token contains:
- Its classification (type)
- The actual text content (value)
- Position information (line and column numbers)

### Keyword, Operator, and Separator Arrays
Static arrays containing the reserved words, operators, and separators of the C language:

```c
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
```

These arrays are used for quick lookup during token classification.

## Core Functions

### Token Classification

#### is_keyword(), is_operator(), is_separator()
Helper functions that check if a given string matches any of the predefined keywords, operators, or separators using linear search through the respective arrays.

#### get_token_type()
Determines the type of a token based on its value by checking against keywords, operators, separators, and applying heuristics for numbers and strings.

### Lexical Analysis

#### tokenize()
The core function that extracts the next token from the source code. It handles:
1. Whitespace skipping
2. Comment recognition and processing
3. String literal extraction
4. Multi-character operator detection
5. Single-character token identification
6. Identifier and keyword parsing
7. Numeric literal recognition
8. Unknown token handling

The function maintains position information (line and column) throughout the process.

#### lex_source()
Processes an entire source string, repeatedly calling tokenize() until EOF is reached, and displays the results.

### Utility Functions

#### print_token()
Formats and displays token information in a human-readable way, showing the token type, position, and value.

## Lexical Analysis Process

### 1. Preprocessing
The lexer first skips whitespace characters (spaces, tabs, newlines) and updates position tracking accordingly.

### 2. Comment Handling
Two types of comments are recognized:
- Single-line comments beginning with //
- Multi-line comments enclosed in /* */

Comments are treated as single tokens and their complete text is preserved.

### 3. String Literal Processing
String literals enclosed in double quotes are extracted as single tokens, preserving their quotes and handling multi-line strings.

### 4. Multi-character Token Recognition
The lexer checks for longer operators first (like ++, ==, <=) before checking for shorter ones to ensure correct tokenization.

### 5. Identifier and Keyword Parsing
Sequences beginning with a letter or underscore, followed by letters, digits, or underscores are parsed as identifiers. They are then checked against the keyword list to determine their final classification.

### 6. Numeric Literal Recognition
Numbers (integers and floating-point) are recognized by scanning sequences of digits and decimal points, with optional leading signs.

### 7. Single-character Token Processing
Individual characters are classified as operators or separators based on predefined lists.

## Position Tracking

The lexer maintains precise position information throughout the analysis:
- Line numbers are incremented when newlines are encountered
- Column numbers are tracked for horizontal positioning
- Token positions are recorded at their starting points

This information is valuable for error reporting in later compilation phases.

## Error Handling

The lexer handles several error conditions:
- Unknown characters are reported as TOKEN_UNKNOWN
- Unterminated string literals are processed as far as possible
- Malformed comments are handled gracefully
- Buffer overflow protection prevents crashes

## Design Decisions

### Static Arrays vs. Hash Tables
The implementation uses static arrays for keywords, operators, and separators rather than hash tables for simplicity. While this results in linear search time, it's acceptable for the small datasets involved and keeps the implementation straightforward.

### Sequential Processing
The lexer processes input sequentially from left to right, which is typical for lexical analyzers and aligns with the linear nature of text.

### State Management
Position tracking is managed through simple integer counters rather than complex state machines, which suffices for this implementation's requirements.

## Performance Considerations

1. **Linear Time Complexity**: Tokenization is O(n) where n is the length of the source code
2. **Minimal Memory Allocation**: Uses static buffers to avoid dynamic memory allocation overhead
3. **Early Termination**: Stops processing at EOF
4. **Batch Output**: Processes entire source at once rather than streaming

## Limitations and Potential Improvements

### Current Limitations
1. **No Character Literals**: Does not recognize 'a', '\n' style literals
2. **No Preprocessor Support**: Ignores #include, #define directives
3. **Limited Escape Sequence Handling**: Does not process escape sequences in strings
4. **No Hexadecimal/Octal Support**: Only recognizes decimal numbers
5. **Basic Error Reporting**: Minimal diagnostic information for errors

### Possible Enhancements
1. **Character Literal Support**: Add recognition for single-quoted literals
2. **Preprocessor Directive Handling**: Process #include, #define, etc.
3. **Escape Sequence Processing**: Interpret \n, \t, \", etc. in strings
4. **Extended Number Formats**: Support hexadecimal (0xFF) and octal (0123) literals
5. **Enhanced Error Diagnostics**: Provide more detailed error messages
6. **Unicode Support**: Handle Unicode identifiers and characters
7. **Streaming Interface**: Process input incrementally rather than all at once
8. **Integration with Parser**: Connect to a syntactic analyzer for a complete front-end

## Educational Value

This project demonstrates:
- Fundamentals of lexical analysis in compilers
- String processing and pattern matching techniques
- State management in sequential processing
- Data structure design for language processing
- Error handling in text processing applications
- Modular design with separation of concerns
- Practical application of arrays and string manipulation