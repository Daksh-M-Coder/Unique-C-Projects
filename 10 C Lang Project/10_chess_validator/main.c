#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BOARD_SIZE 8

// Chess piece representations
#define EMPTY ' '
#define PAWN 'P'
#define ROOK 'R'
#define KNIGHT 'N'
#define BISHOP 'B'
#define QUEEN 'Q'
#define KING 'K'

// Structure to represent a chess position
typedef struct {
    int row;
    int col;
} Position;

// Chess board representation
char board[BOARD_SIZE][BOARD_SIZE];

// Function prototypes
void init_board();
void print_board();
int parse_position(char* notation, Position* pos);
int is_valid_position(Position pos);
int is_valid_move(Position from, Position to, char piece);
int is_valid_pawn_move(Position from, Position to);
int is_valid_rook_move(Position from, Position to);
int is_valid_knight_move(Position from, Position to);
int is_valid_bishop_move(Position from, Position to);
int is_valid_queen_move(Position from, Position to);
int is_valid_king_move(Position from, Position to);
char get_piece(Position pos);
void print_menu();

int main() {
    int choice;
    char from_str[10], to_str[10];
    Position from, to;
    char continueOperation;

    // Initialize the chess board
    init_board();
    
    printf("Welcome to the Chess Move Validator!\n");
    printf("This tool validates chess moves according to standard rules.\n");

    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Display board
                print_board();
                break;

            case 2: // Validate move
                print_board();
                printf("Enter move in format 'e2 e4' (from to): ");
                scanf("%s %s", from_str, to_str);
                
                if (!parse_position(from_str, &from) || !parse_position(to_str, &to)) {
                    printf("Invalid position notation!\n");
                    break;
                }
                
                if (!is_valid_position(from) || !is_valid_position(to)) {
                    printf("Positions must be within the board (a1-h8)!\n");
                    break;
                }
                
                char piece = get_piece(from);
                if (piece == EMPTY) {
                    printf("No piece at the starting position!\n");
                    break;
                }
                
                if (is_valid_move(from, to, piece)) {
                    printf("Move is VALID!\n");
                } else {
                    printf("Move is INVALID!\n");
                }
                break;

            case 3: // Exit
                printf("Thank you for using the Chess Move Validator!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &continueOperation);
        printf("\n");

    } while (continueOperation == 'y' || continueOperation == 'Y');

    return 0;
}

// Initialize the chess board with starting position
void init_board() {
    // Clear the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    
    // Set up pawns
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = tolower(PAWN);  // Black pawns
        board[6][i] = PAWN;           // White pawns
    }
    
    // Set up other pieces (black)
    board[0][0] = tolower(ROOK);
    board[0][1] = tolower(KNIGHT);
    board[0][2] = tolower(BISHOP);
    board[0][3] = tolower(QUEEN);
    board[0][4] = tolower(KING);
    board[0][5] = tolower(BISHOP);
    board[0][6] = tolower(KNIGHT);
    board[0][7] = tolower(ROOK);
    
    // Set up other pieces (white)
    board[7][0] = ROOK;
    board[7][1] = KNIGHT;
    board[7][2] = BISHOP;
    board[7][3] = QUEEN;
    board[7][4] = KING;
    board[7][5] = BISHOP;
    board[7][6] = KNIGHT;
    board[7][7] = ROOK;
}

// Print the chess board
void print_board() {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                printf(". ");
            } else {
                printf("%c ", board[i][j]);
            }
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n\n");
    
    // Legend
    printf("White pieces: Uppercase letters\n");
    printf("Black pieces: Lowercase letters\n");
    printf("P=Pawn, R=Rook, N=Knight, B=Bishop, Q=Queen, K=King\n\n");
}

// Parse algebraic notation to position
int parse_position(char* notation, Position* pos) {
    if (strlen(notation) != 2) {
        return 0;  // Invalid notation
    }
    
    char col_char = notation[0];
    char row_char = notation[1];
    
    // Convert column letter to index (a=0, b=1, ..., h=7)
    if (col_char >= 'a' && col_char <= 'h') {
        pos->col = col_char - 'a';
    } else if (col_char >= 'A' && col_char <= 'H') {
        pos->col = col_char - 'A';
    } else {
        return 0;  // Invalid column
    }
    
    // Convert row number to index (1=7, 2=6, ..., 8=0)
    if (row_char >= '1' && row_char <= '8') {
        pos->row = 8 - (row_char - '0');
    } else {
        return 0;  // Invalid row
    }
    
    return 1;  // Success
}

// Check if position is valid (within board)
int is_valid_position(Position pos) {
    return (pos.row >= 0 && pos.row < BOARD_SIZE && pos.col >= 0 && pos.col < BOARD_SIZE);
}

// Validate move based on piece type
int is_valid_move(Position from, Position to, char piece) {
    // Can't move to the same position
    if (from.row == to.row && from.col == to.col) {
        return 0;
    }
    
    // Can't capture own piece
    if (isupper(piece) && isupper(get_piece(to))) {
        return 0;
    }
    if (islower(piece) && islower(get_piece(to))) {
        return 0;
    }
    
    switch (toupper(piece)) {
        case PAWN:
            return is_valid_pawn_move(from, to);
        case ROOK:
            return is_valid_rook_move(from, to);
        case KNIGHT:
            return is_valid_knight_move(from, to);
        case BISHOP:
            return is_valid_bishop_move(from, to);
        case QUEEN:
            return is_valid_queen_move(from, to);
        case KING:
            return is_valid_king_move(from, to);
        default:
            return 0;  // Unknown piece
    }
}

// Validate pawn move
int is_valid_pawn_move(Position from, Position to) {
    char piece = get_piece(from);
    int direction = isupper(piece) ? -1 : 1;  // White moves up, black moves down
    int start_row = isupper(piece) ? 6 : 1;   // Starting row for each color
    
    // Forward move
    if (from.col == to.col) {
        // Single move forward
        if (to.row == from.row + direction && get_piece(to) == EMPTY) {
            return 1;
        }
        // Double move from starting position
        if (from.row == start_row && to.row == from.row + 2 * direction && 
            get_piece(to) == EMPTY && get_piece((Position){from.row + direction, from.col}) == EMPTY) {
            return 1;
        }
    }
    // Diagonal capture
    else if (abs(from.col - to.col) == 1 && to.row == from.row + direction) {
        if (get_piece(to) != EMPTY && 
            ((isupper(piece) && islower(get_piece(to))) || 
             (islower(piece) && isupper(get_piece(to))))) {
            return 1;
        }
    }
    
    return 0;
}

// Validate rook move
int is_valid_rook_move(Position from, Position to) {
    // Rook moves horizontally or vertically
    if (from.row != to.row && from.col != to.col) {
        return 0;
    }
    
    // Check path is clear
    if (from.row == to.row) {
        // Horizontal move
        int start = (from.col < to.col) ? from.col + 1 : to.col + 1;
        int end = (from.col < to.col) ? to.col : from.col;
        for (int i = start; i < end; i++) {
            if (get_piece((Position){from.row, i}) != EMPTY) {
                return 0;
            }
        }
    } else {
        // Vertical move
        int start = (from.row < to.row) ? from.row + 1 : to.row + 1;
        int end = (from.row < to.row) ? to.row : from.row;
        for (int i = start; i < end; i++) {
            if (get_piece((Position){i, from.col}) != EMPTY) {
                return 0;
            }
        }
    }
    
    return 1;
}

// Validate knight move
int is_valid_knight_move(Position from, Position to) {
    int row_diff = abs(from.row - to.row);
    int col_diff = abs(from.col - to.col);
    
    // Knight moves in an L-shape: 2 squares in one direction, 1 in the other
    return (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2);
}

// Validate bishop move
int is_valid_bishop_move(Position from, Position to) {
    int row_diff = abs(from.row - to.row);
    int col_diff = abs(from.col - to.col);
    
    // Bishop moves diagonally
    if (row_diff != col_diff) {
        return 0;
    }
    
    // Check path is clear
    int row_dir = (to.row > from.row) ? 1 : -1;
    int col_dir = (to.col > from.col) ? 1 : -1;
    
    for (int i = 1; i < row_diff; i++) {
        if (get_piece((Position){from.row + i * row_dir, from.col + i * col_dir}) != EMPTY) {
            return 0;
        }
    }
    
    return 1;
}

// Validate queen move
int is_valid_queen_move(Position from, Position to) {
    // Queen combines rook and bishop moves
    return is_valid_rook_move(from, to) || is_valid_bishop_move(from, to);
}

// Validate king move
int is_valid_king_move(Position from, Position to) {
    int row_diff = abs(from.row - to.row);
    int col_diff = abs(from.col - to.col);
    
    // King moves one square in any direction
    return row_diff <= 1 && col_diff <= 1 && (row_diff != 0 || col_diff != 0);
}

// Get piece at position
char get_piece(Position pos) {
    if (!is_valid_position(pos)) {
        return EMPTY;
    }
    return board[pos.row][pos.col];
}

// Print the menu
void print_menu() {
    printf("\n===== Chess Move Validator =====\n");
    printf("1. Display board\n");
    printf("2. Validate move\n");
    printf("3. Exit\n");
    printf("=============================\n");
}