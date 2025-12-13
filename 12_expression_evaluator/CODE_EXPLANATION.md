# Mathematical Expression Evaluator - Code Explanation

## Program Structure
The mathematical expression evaluator implements a recursive descent parser to tokenize and evaluate arithmetic expressions. It follows standard operator precedence rules and supports parentheses, unary operators, and exponentiation. The program demonstrates compiler construction techniques using only standard C libraries.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
```
- `stdio.h`: For input/output operations
- `stdlib.h`: For `strtod` function to parse numbers
- `string.h`: For string manipulation functions
- `ctype.h`: For character classification functions
- `math.h`: For `pow` function for exponentiation

### Constants
```c
#define MAX_EXPR_LEN 256
#define MAX_TOKENS 100
```
- Maximum expression length and token count for memory management

### Data Structures

#### Token Types
```c
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_POWER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;
```
- Enumerated type for all possible token categories
- Includes operators, parentheses, numbers, and control tokens

#### Token Structure
```c
typedef struct {
    TokenType type;
    double value;  // For numbers
} Token;
```
- Represents a single lexical unit
- Stores both type and numeric value for numbers

#### Parser Structure
```c
typedef struct {
    Token tokens[MAX_TOKENS];
    int pos;
    int count;
} Parser;
```
- Manages token stream and current position
- Facilitates token consumption during parsing

## Detailed Code Walkthrough

### Main Function
```c
int main() {
    char expr[MAX_EXPR_LEN];
    Parser parser;
    double result;
    
    printf("Mathematical Expression Evaluator\n");
    // ... introductory messages ...
    
    while (1) {
        printf("Enter expression: ");
        fgets(expr, sizeof(expr), stdin);
        
        // Remove newline
        expr[strcspn(expr, "\n")] = 0;
        
        // Check for quit command
        if (strcmp(expr, "quit") == 0 || strcmp(expr, "exit") == 0) {
            break;
        }
        
        // Tokenize expression
        tokenize(expr, &parser);
        
        // Parse and evaluate
        parser.pos = 0;
        result = parse_expression(&parser);
        
        if (parser.tokens[parser.pos].type == TOKEN_ERROR) {
            printf("Error: Invalid expression\n");
        } else {
            printf("Result: %.6f\n", result);
        }
        printf("\n");
    }
    
    printf("Goodbye!\n");
    return 0;
}
```
- Provides interactive interface for expression evaluation
- Handles user input and output formatting
- Controls program flow and termination

### Tokenizer (Lexical Analysis)
```c
void tokenize(const char* expr, Parser* parser) {
    parser->count = 0;
    parser->pos = 0;
    
    while (*expr && parser->count < MAX_TOKENS - 1) {
        skip_whitespace(&expr);
        
        if (*expr == '\0') {
            break;
        }
        
        Token* token = &parser->tokens[parser->count];
        
        if (isdigit(*expr) || *expr == '.') {
            // Parse number
            token->type = TOKEN_NUMBER;
            token->value = strtod(expr, (char**)&expr);
        } else {
            // Parse operator
            switch (*expr) {
                case '+':
                    token->type = TOKEN_PLUS;
                    expr++;
                    break;
                // ... other operators ...
                default:
                    token->type = TOKEN_ERROR;
                    expr++;
                    break;
            }
        }
        
        parser->count++;
    }
    
    // Add end token
    parser->tokens[parser->count].type = TOKEN_END;
    parser->count++;
}
```
- Converts character string into sequence of tokens
- Distinguishes between numbers and operators
- Uses `strtod` for robust number parsing
- Handles whitespace skipping

### Recursive Descent Parser
The parser implements a context-free grammar with proper precedence:

#### Expression Level (Addition/Subtraction)
```c
double parse_expression(Parser* parser) {
    double result = parse_term(parser);
    
    while (1) {
        Token token = peek_token(parser);
        if (token.type == TOKEN_PLUS) {
            next_token(parser);  // Consume +
            result += parse_term(parser);
        } else if (token.type == TOKEN_MINUS) {
            next_token(parser);  // Consume -
            result -= parse_term(parser);
        } else {
            break;
        }
    }
    
    return result;
}
```
- Handles lowest precedence operations
- Left-associative parsing for addition/subtraction
- Uses `peek_token` to look ahead without consuming

#### Term Level (Multiplication/Division)
```c
double parse_term(Parser* parser) {
    double result = parse_factor(parser);
    
    while (1) {
        Token token = peek_token(parser);
        if (token.type == TOKEN_MULTIPLY) {
            next_token(parser);  // Consume *
            result *= parse_factor(parser);
        } else if (token.type == TOKEN_DIVIDE) {
            next_token(parser);  // Consume /
            double divisor = parse_factor(parser);
            if (divisor == 0) {
                printf("Error: Division by zero\n");
                return 0;
            }
            result /= divisor;
        } else {
            break;
        }
    }
    
    return result;
}
```
- Handles medium precedence operations
- Left-associative parsing for multiplication/division
- Includes division by zero checking

#### Factor Level (Exponentiation)
```c
double parse_factor(Parser* parser) {
    double result = parse_power(parser);
    
    // Right associative for power
    Token token = peek_token(parser);
    if (token.type == TOKEN_POWER) {
        next_token(parser);  // Consume ^
        result = pow(result, parse_factor(parser));
    }
    
    return result;
}
```
- Handles highest precedence operation (exponentiation)
- Right-associative parsing for proper mathematical semantics
- Uses `pow` function for computation

#### Power Level (Unary Operators)
```c
double parse_power(Parser* parser) {
    Token token = peek_token(parser);
    
    if (token.type == TOKEN_MINUS) {
        next_token(parser);  // Consume -
        return -parse_primary(parser);
    } else if (token.type == TOKEN_PLUS) {
        next_token(parser);  // Consume +
        return parse_primary(parser);
    } else {
        return parse_primary(parser);
    }
}
```
- Handles unary plus and minus operators
- Higher precedence than binary operators
- Simple recursive application

#### Primary Level (Numbers/Parentheses)
```c
double parse_primary(Parser* parser) {
    Token token = next_token(parser);
    
    if (token.type == TOKEN_NUMBER) {
        return token.value;
    } else if (token.type == TOKEN_LPAREN) {
        double result = parse_expression(parser);
        token = next_token(parser);
        if (token.type != TOKEN_RPAREN) {
            printf("Error: Missing closing parenthesis\n");
            parser->tokens[parser->pos].type = TOKEN_ERROR;
        }
        return result;
    } else {
        printf("Error: Unexpected token\n");
        parser->tokens[parser->pos].type = TOKEN_ERROR;
        return 0;
    }
}
```
- Handles atomic expressions (numbers and parenthesized expressions)
- Recursively calls higher-level parsers for nested expressions
- Validates balanced parentheses

### Helper Functions

#### Token Management
```c
Token next_token(Parser* parser) {
    if (parser->pos < parser->count) {
        return parser->tokens[parser->pos++];
    }
    Token end_token = {TOKEN_END, 0};
    return end_token;
}

Token peek_token(Parser* parser) {
    if (parser->pos < parser->count) {
        return parser->tokens[parser->pos];
    }
    Token end_token = {TOKEN_END, 0};
    return end_token;
}
```
- `next_token`: Consumes and returns current token
- `peek_token`: Inspects current token without consuming

#### Whitespace Handling
```c
void skip_whitespace(const char** expr) {
    while (**expr && isspace(**expr)) {
        (*expr)++;
    }
}
```
- Advances pointer past whitespace characters
- Uses `isspace` for portable whitespace detection

## Grammar and Precedence
The implemented grammar correctly handles operator precedence:
```
expression → term (('+' | '-') term)*
term → factor (('*' | '/') factor)*
factor → power ('^' factor)?
power → ('-' | '+')? primary
primary → NUMBER | '(' expression ')'
```

This ensures expressions like `2 + 3 * 4` are parsed as `2 + (3 * 4)` rather than `(2 + 3) * 4`.

## Program Flow
1. User enters mathematical expression
2. Expression is tokenized into sequence of tokens
3. Parser recursively evaluates expression according to grammar
4. Result is displayed to user
5. Loop continues until user requests exit

## Learning Points
1. **Recursive Descent Parsing**: Top-down parsing technique
2. **Operator Precedence**: Implementing mathematical rules
3. **Associativity**: Left vs right associative operators
4. **Error Handling**: Graceful handling of invalid input
5. **Grammar Design**: Translating mathematical rules to code
6. **Token Management**: Lexical analysis fundamentals

## Limitations and Possible Improvements
1. **Limited Functions**: No trigonometric or logarithmic functions
2. **No Variables**: Cannot store and recall values
3. **Simple Error Messages**: Basic error reporting only
4. **No Expression History**: Previous calculations not stored
5. **Fixed Grammar**: Cannot easily extend with new operators
6. **No Optimization**: Expressions evaluated directly without optimization