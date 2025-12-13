#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 256
#define MAX_SOURCE_LEN 4096

// Token types
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

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
    int line;
    int column;
} Token;

// Keywords
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const int NUM_KEYWORDS = sizeof(keywords) / sizeof(keywords[0]);

// Operators
const char* operators[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "!", "&", "|",
    "&&", "||", "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<", ">>"
};

const int NUM_OPERATORS = sizeof(operators) / sizeof(operators[0]);

// Separators
const char* separators[] = {
    "(", ")", "{", "}", "[", "]", ";", ",", ".", "->", "..."
};

const int NUM_SEPARATORS = sizeof(separators) / sizeof(separators[0]);

// Function prototypes
TokenType get_token_type(const char* value);
int is_keyword(const char* word);
int is_operator(const char* op);
int is_separator(const char* sep);
Token tokenize(const char** source, int* line, int* column);
void print_token(Token token);
void lex_source(const char* source);

// Check if word is a keyword
int is_keyword(const char* word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if string is an operator
int is_operator(const char* op) {
    for (int i = 0; i < NUM_OPERATORS; i++) {
        if (strcmp(op, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if string is a separator
int is_separator(const char* sep) {
    for (int i = 0; i < NUM_SEPARATORS; i++) {
        if (strcmp(sep, separators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Determine token type based on value
TokenType get_token_type(const char* value) {
    if (is_keyword(value)) {
        return TOKEN_KEYWORD;
    }
    
    if (is_operator(value)) {
        return TOKEN_OPERATOR;
    }
    
    if (is_separator(value)) {
        return TOKEN_SEPARATOR;
    }
    
    // Check if it's a number
    int len = strlen(value);
    int is_num = 1;
    for (int i = 0; i < len; i++) {
        if (!isdigit(value[i]) && (i > 0 || value[i] != '.')) {
            is_num = 0;
            break;
        }
    }
    
    if (is_num && len > 0) {
        return TOKEN_NUMBER;
    }
    
    // Check if it's a string literal
    if (len >= 2 && value[0] == '"' && value[len-1] == '"') {
        return TOKEN_STRING;
    }
    
    // Assume it's an identifier
    return TOKEN_IDENTIFIER;
}

// Print token information
void print_token(Token token) {
    const char* type_str;
    switch (token.type) {
        case TOKEN_IDENTIFIER: type_str = "IDENTIFIER"; break;
        case TOKEN_NUMBER: type_str = "NUMBER"; break;
        case TOKEN_STRING: type_str = "STRING"; break;
        case TOKEN_OPERATOR: type_str = "OPERATOR"; break;
        case TOKEN_KEYWORD: type_str = "KEYWORD"; break;
        case TOKEN_SEPARATOR: type_str = "SEPARATOR"; break;
        case TOKEN_COMMENT: type_str = "COMMENT"; break;
        case TOKEN_EOF: type_str = "EOF"; break;
        default: type_str = "UNKNOWN"; break;
    }
    
    printf("Line %d, Col %d: %-12s %s\n", token.line, token.column, type_str, token.value);
}

// Tokenize the next token from source
Token tokenize(const char** source, int* line, int* column) {
    Token token;
    token.line = *line;
    token.column = *column;
    token.value[0] = '\0';
    
    // Skip whitespace
    while (**source && isspace(**source)) {
        if (**source == '\n') {
            (*line)++;
            *column = 1;
        } else {
            (*column)++;
        }
        (*source)++;
    }
    
    // End of file
    if (**source == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.value, "EOF");
        return token;
    }
    
    // Save starting position for token
    int start_column = *column;
    token.line = *line;
    token.column = start_column;
    
    // Handle single line comments
    if (**source == '/' && *(*source + 1) == '/') {
        token.type = TOKEN_COMMENT;
        int i = 0;
        while (**source && **source != '\n') {
            token.value[i++] = **source;
            (*source)++;
            (*column)++;
        }
        token.value[i] = '\0';
        return token;
    }
    
    // Handle multi-line comments
    if (**source == '/' && *(*source + 1) == '*') {
        token.type = TOKEN_COMMENT;
        int i = 0;
        token.value[i++] = **source; (*source)++; (*column)++;
        token.value[i++] = **source; (*source)++; (*column)++;
        
        while (**source && !(**source == '*' && *(*source + 1) == '/')) {
            token.value[i++] = **source;
            if (**source == '\n') {
                (*line)++;
                *column = 1;
            } else {
                (*column)++;
            }
            (*source)++;
        }
        
        if (**source == '*' && *(*source + 1) == '/') {
            token.value[i++] = **source; (*source)++; (*column)++;
            token.value[i++] = **source; (*source)++; (*column)++;
        }
        
        token.value[i] = '\0';
        return token;
    }
    
    // Handle string literals
    if (**source == '"') {
        int i = 0;
        token.value[i++] = **source;
        (*source)++;
        (*column)++;
        
        while (**source && **source != '"') {
            token.value[i++] = **source;
            if (**source == '\n') {
                (*line)++;
                *column = 1;
            } else {
                (*column)++;
            }
            (*source)++;
        }
        
        if (**source == '"') {
            token.value[i++] = **source;
            (*source)++;
            (*column)++;
        }
        
        token.value[i] = '\0';
        token.type = TOKEN_STRING;
        return token;
    }
    
    // Handle operators and separators (multi-character)
    // Check for multi-character operators first
    char two_char[3] = {**source, *(*source + 1), '\0'};
    char three_char[4] = {**source, *(*source + 1), *(*source + 2), '\0'};
    
    // Check for 3-character operators
    if (is_operator(three_char)) {
        strcpy(token.value, three_char);
        token.type = TOKEN_OPERATOR;
        (*source) += 3;
        *column += 3;
        return token;
    }
    
    // Check for 2-character operators
    if (is_operator(two_char)) {
        strcpy(token.value, two_char);
        token.type = TOKEN_OPERATOR;
        (*source) += 2;
        *column += 2;
        return token;
    }
    
    // Check for single-character operators/separators
    char one_char[2] = {**source, '\0'};
    if (is_operator(one_char) || is_separator(one_char)) {
        strcpy(token.value, one_char);
        token.type = is_operator(one_char) ? TOKEN_OPERATOR : TOKEN_SEPARATOR;
        (*source)++;
        (*column)++;
        return token;
    }
    
    // Handle identifiers and keywords
    if (isalpha(**source) || **source == '_') {
        int i = 0;
        while (**source && (isalnum(**source) || **source == '_')) {
            token.value[i++] = **source;
            (*source)++;
            (*column)++;
        }
        token.value[i] = '\0';
        token.type = get_token_type(token.value);
        return token;
    }
    
    // Handle numbers
    if (isdigit(**source) || (**source == '.' && isdigit(*(*source + 1)))) {
        int i = 0;
        // Handle possible leading sign
        if (**source == '-' || **source == '+') {
            token.value[i++] = **source;
            (*source)++;
            (*column)++;
        }
        
        // Handle digits and decimal point
        while (**source && (isdigit(**source) || **source == '.')) {
            token.value[i++] = **source;
            (*source)++;
            (*column)++;
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }
    
    // Unknown token
    token.value[0] = **source;
    token.value[1] = '\0';
    token.type = TOKEN_UNKNOWN;
    (*source)++;
    (*column)++;
    return token;
}

// Lex the entire source code
void lex_source(const char* source) {
    const char* ptr = source;
    int line = 1;
    int column = 1;
    
    printf("Lexical Analysis Results:\n");
    printf("========================\n");
    
    Token token;
    do {
        token = tokenize(&ptr, &line, &column);
        if (token.type != TOKEN_EOF) {
            print_token(token);
        }
    } while (token.type != TOKEN_EOF);
}

int main() {
    printf("Compiler Lexer - A simple lexical analyzer for C code\n");
    printf("This program tokenizes C source code and identifies different token types.\n\n");
    
    // Sample C code to tokenize
    const char* sample_code = 
        "// This is a sample C program\n"
        "#include <stdio.h>\n\n"
        "int main() {\n"
        "    int x = 10;\n"
        "    float y = 3.14;\n"
        "    char* str = \"Hello, World!\";\n"
        "    \n"
        "    if (x > 5) {\n"
        "        printf(\"x is greater than 5\\n\");\n"
        "    }\n"
        "    \n"
        "    for (int i = 0; i < x; i++) {\n"
        "        y += 0.1;\n"
        "    }\n"
        "    \n"
        "    return 0;\n"
        "}\n";
    
    printf("Sample C code to tokenize:\n");
    printf("--------------------------\n");
    printf("%s\n", sample_code);
    
    printf("\nTokenization results:\n");
    printf("---------------------\n");
    lex_source(sample_code);
    
    // Interactive mode
    printf("\nInteractive Mode:\n");
    printf("-----------------\n");
    printf("Enter your own C code (press Ctrl+C to exit):\n");
    
    char input_buffer[MAX_SOURCE_LEN];
    char* input_ptr = input_buffer;
    int ch;
    
    while ((ch = getchar()) != EOF && (input_ptr - input_buffer) < MAX_SOURCE_LEN - 1) {
        *input_ptr++ = (char)ch;
    }
    *input_ptr = '\0';
    
    if (strlen(input_buffer) > 0) {
        printf("\nTokenization results for your input:\n");
        printf("------------------------------------\n");
        lex_source(input_buffer);
    }
    
    return 0;
}