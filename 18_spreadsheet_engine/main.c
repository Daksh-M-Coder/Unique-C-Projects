#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_ROWS 100
#define MAX_COLS 26  // A-Z
#define MAX_CELL_LEN 256
#define MAX_FORMULA_LEN 256
#define MAX_TOKENS 64

// Cell structure
typedef struct {
    char value[MAX_CELL_LEN];      // Display value
    char formula[MAX_FORMULA_LEN]; // Original formula
    double numeric_value;          // Computed numeric value
    int is_formula;                // Flag indicating if cell contains formula
} Cell;

// Spreadsheet grid
Cell spreadsheet[MAX_ROWS][MAX_COLS];

// Token types for formula parsing
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_CELL_REF,
    TOKEN_FUNCTION,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_CELL_LEN];
    double number;
} Token;

// Function prototypes
void init_spreadsheet();
void display_spreadsheet();
void set_cell(int row, int col, const char* value);
double evaluate_formula(const char* formula, int* error);
Token get_next_token(const char** formula_ptr);
double parse_expression(const char** formula_ptr, int* error);
double parse_term(const char** formula_ptr, int* error);
double parse_factor(const char** formula_ptr, int* error);
double get_cell_value(int row, int col, int* error);
int parse_cell_reference(const char* ref, int* row, int* col);
void print_menu();

// Initialize spreadsheet
void init_spreadsheet() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            spreadsheet[i][j].value[0] = '\0';
            spreadsheet[i][j].formula[0] = '\0';
            spreadsheet[i][j].numeric_value = 0.0;
            spreadsheet[i][j].is_formula = 0;
        }
    }
}

// Display spreadsheet
void display_spreadsheet() {
    printf("\n   ");
    for (int j = 0; j < 10; j++) {
        printf("     %c     ", 'A' + j);
    }
    printf("\n");
    
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i+1);
        for (int j = 0; j < 10; j++) {
            if (strlen(spreadsheet[i][j].value) > 0) {
                printf("|%7.7s", spreadsheet[i][j].value);
            } else {
                printf("|       ");
            }
        }
        printf("|\n");
    }
    printf("\n");
}

// Set cell value
void set_cell(int row, int col, const char* value) {
    if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLS) {
        printf("Error: Invalid cell reference\n");
        return;
    }
    
    strncpy(spreadsheet[row][col].formula, value, MAX_FORMULA_LEN - 1);
    spreadsheet[row][col].formula[MAX_FORMULA_LEN - 1] = '\0';
    
    // Check if it's a formula (starts with =)
    if (value[0] == '=') {
        spreadsheet[row][col].is_formula = 1;
        int error = 0;
        double result = evaluate_formula(value + 1, &error); // Skip '='
        
        if (error) {
            strcpy(spreadsheet[row][col].value, "ERROR");
            spreadsheet[row][col].numeric_value = 0.0;
        } else {
            spreadsheet[row][col].numeric_value = result;
            snprintf(spreadsheet[row][col].value, MAX_CELL_LEN, "%.2f", result);
        }
    } else {
        spreadsheet[row][col].is_formula = 0;
        strncpy(spreadsheet[row][col].value, value, MAX_CELL_LEN - 1);
        spreadsheet[row][col].value[MAX_CELL_LEN - 1] = '\0';
        
        // Try to convert to number
        char* endptr;
        double num = strtod(value, &endptr);
        if (*endptr == '\0') { // Entire string is a number
            spreadsheet[row][col].numeric_value = num;
        } else {
            spreadsheet[row][col].numeric_value = 0.0;
        }
    }
}

// Parse cell reference (e.g., "A1", "B10")
int parse_cell_reference(const char* ref, int* row, int* col) {
    if (!ref || strlen(ref) < 2) return 0;
    
    // First character should be a letter (column)
    if (ref[0] < 'A' || ref[0] > 'Z') return 0;
    *col = ref[0] - 'A';
    
    // Remaining characters should be digits (row)
    char* endptr;
    long row_val = strtol(ref + 1, &endptr, 10);
    if (*endptr != '\0' || row_val < 1 || row_val > MAX_ROWS) return 0;
    
    *row = (int)row_val - 1; // Convert to 0-based index
    return 1;
}

// Get cell value
double get_cell_value(int row, int col, int* error) {
    if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLS) {
        *error = 1;
        return 0.0;
    }
    
    *error = 0;
    return spreadsheet[row][col].numeric_value;
}

// Get next token from formula
Token get_next_token(const char** formula_ptr) {
    Token token;
    token.type = TOKEN_EOF;
    token.value[0] = '\0';
    token.number = 0.0;
    
    // Skip whitespace
    while (**formula_ptr == ' ' || **formula_ptr == '\t') {
        (*formula_ptr)++;
    }
    
    // End of formula
    if (**formula_ptr == '\0') {
        return token;
    }
    
    // Number
    if (isdigit(**formula_ptr) || **formula_ptr == '.') {
        char* endptr;
        token.number = strtod(*formula_ptr, &endptr);
        token.type = TOKEN_NUMBER;
        strncpy(token.value, *formula_ptr, endptr - *formula_ptr);
        token.value[endptr - *formula_ptr] = '\0';
        *formula_ptr = endptr;
        return token;
    }
    
    // Cell reference (e.g., A1, B10)
    if (**formula_ptr >= 'A' && **formula_ptr <= 'Z') {
        const char* start = *formula_ptr;
        (*formula_ptr)++; // Skip column letter
        
        // Skip digits
        while (isdigit(**formula_ptr)) {
            (*formula_ptr)++;
        }
        
        token.type = TOKEN_CELL_REF;
        strncpy(token.value, start, *formula_ptr - start);
        token.value[*formula_ptr - start] = '\0';
        return token;
    }
    
    // Operators
    switch (**formula_ptr) {
        case '+':
            token.type = TOKEN_OPERATOR;
            token.value[0] = '+';
            token.value[1] = '\0';
            (*formula_ptr)++;
            return token;
        case '-':
            token.type = TOKEN_OPERATOR;
            token.value[0] = '-';
            token.value[1] = '\0';
            (*formula_ptr)++;
            return token;
        case '*':
            token.type = TOKEN_OPERATOR;
            token.value[0] = '*';
            token.value[1] = '\0';
            (*formula_ptr)++;
            return token;
        case '/':
            token.type = TOKEN_OPERATOR;
            token.value[0] = '/';
            token.value[1] = '\0';
            (*formula_ptr)++;
            return token;
        case '(':
            token.type = TOKEN_LPAREN;
            token.value[0] = '(';
            token.value[1] = '\0';
            (*formula_ptr)++;
            return token;
        case ')':
            token.type = TOKEN_RPAREN;
            token.value[0] = ')';
            token.value[1] = '\0';
            (*formula_ptr)++;
            return token;
    }
    
    // Unknown token
    (*formula_ptr)++;
    return token;
}

// Parse factor (numbers, cell references, parentheses)
double parse_factor(const char** formula_ptr, int* error) {
    Token token = get_next_token(formula_ptr);
    
    switch (token.type) {
        case TOKEN_NUMBER:
            return token.number;
            
        case TOKEN_CELL_REF: {
            int row, col;
            if (!parse_cell_reference(token.value, &row, &col)) {
                *error = 1;
                return 0.0;
            }
            return get_cell_value(row, col, error);
        }
            
        case TOKEN_LPAREN: {
            double result = parse_expression(formula_ptr, error);
            if (*error) return 0.0;
            
            // Expect closing parenthesis
            Token next = get_next_token(formula_ptr);
            if (next.type != TOKEN_RPAREN) {
                *error = 1;
                return 0.0;
            }
            return result;
        }
            
        default:
            *error = 1;
            return 0.0;
    }
}

// Parse term (factors with * or /)
double parse_term(const char** formula_ptr, int* error) {
    double result = parse_factor(formula_ptr, error);
    if (*error) return 0.0;
    
    Token token = get_next_token(formula_ptr);
    while (token.type == TOKEN_OPERATOR && (token.value[0] == '*' || token.value[0] == '/')) {
        double next = parse_factor(formula_ptr, error);
        if (*error) return 0.0;
        
        if (token.value[0] == '*') {
            result *= next;
        } else {
            if (next == 0.0) {
                *error = 1; // Division by zero
                return 0.0;
            }
            result /= next;
        }
        
        token = get_next_token(formula_ptr);
    }
    
    // Put back the last token
    // Note: In a real implementation, we'd need a more sophisticated tokenizer
    // For simplicity, we'll just continue with the current approach
    
    return result;
}

// Parse expression (terms with + or -)
double parse_expression(const char** formula_ptr, int* error) {
    double result = parse_term(formula_ptr, error);
    if (*error) return 0.0;
    
    Token token = get_next_token(formula_ptr);
    while (token.type == TOKEN_OPERATOR && (token.value[0] == '+' || token.value[0] == '-')) {
        double next = parse_term(formula_ptr, error);
        if (*error) return 0.0;
        
        if (token.value[0] == '+') {
            result += next;
        } else {
            result -= next;
        }
        
        token = get_next_token(formula_ptr);
    }
    
    return result;
}

// Evaluate formula
double evaluate_formula(const char* formula, int* error) {
    *error = 0;
    const char* ptr = formula;
    double result = parse_expression(&ptr, error);
    return result;
}

// Print menu
void print_menu() {
    printf("\n=== Spreadsheet Engine ===\n");
    printf("1. Display spreadsheet\n");
    printf("2. Set cell value\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");
}

int main() {
    printf("Spreadsheet Engine - A simple spreadsheet application\n");
    printf("Supports basic formulas with cell references (e.g., =A1+B2)\n");
    
    // Initialize spreadsheet
    init_spreadsheet();
    
    // Demo data
    set_cell(0, 0, "10");      // A1 = 10
    set_cell(0, 1, "20");      // B1 = 20
    set_cell(0, 2, "=A1+B1");  // C1 = A1+B1 = 30
    set_cell(1, 0, "5");       // A2 = 5
    set_cell(1, 1, "=A1*A2");  // B2 = A1*A2 = 50
    set_cell(1, 2, "=C1/B2");  // C2 = C1/B2 = 0.6
    
    int choice;
    char input[256];
    char cell_ref[10];
    int row, col;
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                display_spreadsheet();
                break;
                
            case 2:
                printf("Enter cell reference (e.g., A1): ");
                scanf("%s", cell_ref);
                
                if (!parse_cell_reference(cell_ref, &row, &col)) {
                    printf("Invalid cell reference!\n");
                    break;
                }
                
                printf("Enter value or formula: ");
                scanf("%s", input);
                set_cell(row, col, input);
                printf("Cell %s set to %s\n", cell_ref, input);
                break;
                
            case 3:
                printf("Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
    
    return 0;
}