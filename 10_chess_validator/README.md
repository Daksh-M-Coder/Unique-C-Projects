# Chess Move Validator

## Description
A chess move validation tool that checks if moves conform to standard chess rules. The program implements move validation for all chess pieces including pawns, rooks, knights, bishops, queens, and kings. It displays a chess board and allows users to test moves using standard algebraic notation.

## Features
- Complete chess board initialization with standard starting position
- Visual board display with algebraic notation
- Move validation for all chess pieces
- Support for captures and special movement rules
- Algebraic notation input (e.g., "e2 e4")
- Proper piece color handling (uppercase for white, lowercase for black)

## Chess Rules Implemented
1. **Pawn Movement**: Forward moves (single or double from starting position), diagonal captures
2. **Rook Movement**: Horizontal and vertical moves with path checking
3. **Knight Movement**: L-shaped moves (2 squares in one direction, 1 in perpendicular)
4. **Bishop Movement**: Diagonal moves with path checking
5. **Queen Movement**: Combination of rook and bishop moves
6. **King Movement**: One square in any direction
7. **Capture Rules**: Cannot capture own pieces
8. **Board Boundaries**: Moves must stay within the 8×8 board

## Data Structures Used
1. **Board Representation**: 8×8 2D character array
2. **Position Structure**: Row/column coordinates for board positions
   ```c
   typedef struct {
       int row;
       int col;
   } Position;
   ```

## Standard Library Functions Used
- `stdio.h` - For input/output operations (`printf`, `scanf`)
- `stdlib.h` - For standard library functions (`exit`)
- `ctype.h` - For character handling functions (`toupper`, `tolower`, `isupper`, `islower`)
- `string.h` - For string operations (`strlen`)

## How to Compile and Run

### Compilation
```bash
gcc -o chess_validator main.c
```

### Execution
```bash
./chess_validator
```

On Windows:
```bash
chess_validator.exe
```

## How to Use
1. Run the program
2. Select an operation from the menu:
   - Display board: Show the current chess board
   - Validate move: Test if a move is valid
   - Exit: Quit the program
3. For move validation:
   - Enter moves in algebraic notation format: "from_position to_position"
   - Example: "e2 e4" (move pawn from e2 to e4)
4. View the validation result (VALID or INVALID)
5. Choose to continue or exit

## Sample Output
```
Welcome to the Chess Move Validator!
This tool validates chess moves according to standard rules.

===== Chess Move Validator =====
1. Display board
2. Validate move
3. Exit
=============================
Enter your choice: 1

  a b c d e f g h
8 r n b q k b n r
7 p p p p p p p p
6 . . . . . . . .
5 . . . . . . . .
4 . . . . . . . .
3 . . . . . . . .
2 P P P P P P P P
1 R N B Q K B N R
  a b c d e f g h

White pieces: Uppercase letters
Black pieces: Lowercase letters
P=Pawn, R=Rook, N=Knight, B=Bishop, Q=Queen, K=King
```

## Algebraic Notation
Moves are entered using standard algebraic notation:
- Columns: a, b, c, d, e, f, g, h (left to right)
- Rows: 1, 2, 3, 4, 5, 6, 7, 8 (bottom to top)
- Examples:
  - "e2 e4": Move piece from e2 to e4
  - "g1 f3": Move knight from g1 to f3
  - "e7 e5": Move black pawn from e7 to e5

## Piece Representation
- **Uppercase letters**: White pieces
- **Lowercase letters**: Black pieces
- P/p: Pawn
- R/r: Rook
- N/n: Knight
- B/b: Bishop
- Q/q: Queen
- K/k: King
- . : Empty square

## Educational Value
This implementation demonstrates:
1. 2D array manipulation for board games
2. Implementation of complex rule sets
3. Coordinate system translation (algebraic notation to array indices)
4. Path checking algorithms for sliding pieces
5. Conditional logic for different piece movements
6. Data validation and error handling