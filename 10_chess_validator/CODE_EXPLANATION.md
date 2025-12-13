# Chess Move Validator - Code Explanation

## Program Structure
The chess move validator implements standard chess movement rules for all pieces. It uses a 2D array to represent the board and validates moves according to each piece's specific movement patterns. The program handles algebraic notation input and provides visual feedback on move validity.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
```
- `stdio.h`: For input/output operations
- `stdlib.h`: For standard library functions like `exit()`
- `ctype.h`: For character handling functions (`toupper`, `tolower`, etc.)
- `string.h`: For string operations like `strlen()`

### Constants
```c
#define BOARD_SIZE 8
#define EMPTY ' '
#define PAWN 'P'
#define ROOK 'R'
#define KNIGHT 'N'
#define BISHOP 'B'
#define QUEEN 'Q'
#define KING 'K'
```
- Board dimensions and piece representations
- `EMPTY` represents vacant squares
- Piece constants use standard chess notation

### Data Structures
```c
typedef struct {
    int row;
    int col;
} Position;
```
- `Position`: Represents coordinates on the chess board
- Row and column indices for board positions

### Global Variables
```c
char board[BOARD_SIZE][BOARD_SIZE];
```
- 8×8 2D array representing the chess board
- Each cell contains a piece character or EMPTY

### Function Prototypes
```c
void init_board();
void print_board();
int parse_position(char* notation, Position* pos);
int is_valid_position(Position pos);
int is_valid_move(Position from, Position to, char piece);
// ... specific move validation functions for each piece
char get_piece(Position pos);
void print_menu();
```
- Board management functions
- Position handling and validation
- Piece-specific move validation functions
- User interface functions

## Detailed Code Walkthrough

### Board Initialization
```c
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
    // ... continue for all back rank pieces
    
    // Set up other pieces (white)
    board[7][0] = ROOK;
    board[7][1] = KNIGHT;
    // ... continue for all back rank pieces
}
```
- Initializes board to empty state
- Places pawns on rows 2 and 7 (indices 1 and 6)
- Places major pieces on rows 1 and 8 (indices 0 and 7)
- Uses `tolower()` for black pieces (lowercase) and uppercase for white

### Board Display
```c
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
```
- Displays board with algebraic notation coordinates
- Uses dots for empty squares for better readability
- Shows piece legend for user reference

### Algebraic Notation Parsing
```c
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
```
- Converts algebraic notation (e.g., "e4") to array indices
- Handles both uppercase and lowercase column letters
- Maps row numbers to array indices (inverted because row 1 is at array index 7)

### Generic Move Validation
```c
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
```
- Performs general validation checks applicable to all pieces
- Prevents self-capture using `isupper()`/`islower()` functions
- Dispatches to piece-specific validation functions

### Pawn Move Validation
```c
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
```
- Implements pawn-specific movement rules:
  - Forward movement (single or double from starting position)
  - Diagonal capture only
  - Direction depends on piece color
  - Path checking for double moves

### Rook Move Validation
```c
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
```
- Validates horizontal or vertical movement only
- Checks that path is clear of other pieces
- Uses loop to check intermediate squares

### Knight Move Validation
```c
int is_valid_knight_move(Position from, Position to) {
    int row_diff = abs(from.row - to.row);
    int col_diff = abs(from.col - to.col);
    
    // Knight moves in an L-shape: 2 squares in one direction, 1 in the other
    return (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2);
}
```
- Simple geometric validation for L-shaped moves
- Knights can jump over other pieces, so no path checking needed

### Bishop Move Validation
```c
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
```
- Validates diagonal movement only
- Checks that path is clear using directional increments
- Loops through diagonal path to check for obstructions

### Queen and King Move Validation
```c
int is_valid_queen_move(Position from, Position to) {
    // Queen combines rook and bishop moves
    return is_valid_rook_move(from, to) || is_valid_bishop_move(from, to);
}

int is_valid_king_move(Position from, Position to) {
    int row_diff = abs(from.row - to.row);
    int col_diff = abs(from.col - to.col);
    
    // King moves one square in any direction
    return row_diff <= 1 && col_diff <= 1 && (row_diff != 0 || col_diff != 0);
}
```
- Queen moves like combination of rook and bishop
- King moves one square in any direction (but not staying in place)

## Program Flow
1. Initialize chess board with standard starting position
2. Present menu to user
3. Process user selections:
   - Display current board state
   - Validate moves by:
     * Parsing algebraic notation input
     * Checking position validity
     * Verifying piece exists at starting position
     * Validating move according to piece rules
4. Display validation results
5. Continue until user exits

## Learning Points
1. **2D Array Manipulation**: Working with matrix data structures
2. **Coordinate Systems**: Translating between user notation and array indices
3. **Rule Implementation**: Converting game rules to algorithmic logic
4. **Path Checking**: Validating that intermediate squares are unoccupied
5. **Conditional Logic**: Complex decision-making for different piece types
6. **Data Validation**: Input sanitization and error checking
7. **Modular Design**: Separating concerns into specific functions

## Limitations and Possible Improvements
1. **No Check/Checkmate Detection**: Does not validate moves in context of king safety
2. **No En Passant**: Advanced pawn capture rule not implemented
3. **No Castling**: Special king-rook move not supported
4. **No Promotion**: Pawn promotion when reaching opposite side not handled
5. **Static Board**: No actual move execution, only validation
6. **No Game State**: No tracking of turn, captured pieces, etc.
7. **No Advanced Validation**: Does not consider pins, discovered checks, etc.