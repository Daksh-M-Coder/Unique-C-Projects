#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR_LEN 256
#define MAX_TOKENS 100

// Token types
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

// Token structure
typedef struct {
    TokenType type;
    double value;  // For numbers
} Token;

// Parser structure
typedef struct {
    Token tokens[MAX_TOKENS];
    int pos;
    int count;
} Parser;

// Function prototypes
void tokenize(const char* expr, Parser* parser);
Token next_token(Parser* parser);
Token peek_token(Parser* parser);
void skip_whitespace(const char** expr);
double parse_expression(Parser* parser);
double parse_term(Parser* parser);
double parse_factor(Parser* parser);
double parse_power(Parser* parser);
double parse_primary(Parser* parser);
void print_tokens(Parser* parser);

int main() {
    char expr[MAX_EXPR_LEN];
    Parser parser;
    double result;
    
    printf("Mathematical Expression Evaluator\n");
    printf("Supported operations: +, -, *, /, ^ (power), parentheses\n");
    printf("Type 'quit' to exit\n\n");
    
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
        
        // Uncomment the next line to see tokens
        // print_tokens(&parser);
        
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

// Tokenize the expression
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
                case '-':
                    token->type = TOKEN_MINUS;
                    expr++;
                    break;
                case '*':
                    token->type = TOKEN_MULTIPLY;
                    expr++;
                    break;
                case '/':
                    token->type = TOKEN_DIVIDE;
                    expr++;
                    break;
                case '^':
                    token->type = TOKEN_POWER;
                    expr++;
                    break;
                case '(':
                    token->type = TOKEN_LPAREN;
                    expr++;
                    break;
                case ')':
                    token->type = TOKEN_RPAREN;
                    expr++;
                    break;
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

// Get next token
Token next_token(Parser* parser) {
    if (parser->pos < parser->count) {
        return parser->tokens[parser->pos++];
    }
    Token end_token = {TOKEN_END, 0};
    return end_token;
}

// Peek at next token without consuming it
Token peek_token(Parser* parser) {
    if (parser->pos < parser->count) {
        return parser->tokens[parser->pos];
    }
    Token end_token = {TOKEN_END, 0};
    return end_token;
}

// Skip whitespace characters
void skip_whitespace(const char** expr) {
    while (**expr && isspace(**expr)) {
        (*expr)++;
    }
}

// Parse an expression (handles + and -)
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

// Parse a term (handles * and /)
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

// Parse a factor (handles ^)
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

// Parse a power (handles unary minus)
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

// Parse a primary (numbers and parentheses)
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

// Print tokens for debugging
void print_tokens(Parser* parser) {
    printf("Tokens: ");
    for (int i = 0; i < parser->count; i++) {
        Token token = parser->tokens[i];
        switch (token.type) {
            case TOKEN_NUMBER:
                printf("%.2f ", token.value);
                break;
            case TOKEN_PLUS:
                printf("+ ");
                break;
            case TOKEN_MINUS:
                printf("- ");
                break;
            case TOKEN_MULTIPLY:
                printf("* ");
                break;
            case TOKEN_DIVIDE:
                printf("/ ");
                break;
            case TOKEN_POWER:
                printf("^ ");
                break;
            case TOKEN_LPAREN:
                printf("( ");
                break;
            case TOKEN_RPAREN:
                printf(") ");
                break;
            case TOKEN_END:
                printf("END ");
                break;
            case TOKEN_ERROR:
                printf("ERROR ");
                break;
        }
    }
    printf("\n");
}