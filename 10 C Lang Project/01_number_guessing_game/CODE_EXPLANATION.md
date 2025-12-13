# Number Guessing Game - Code Explanation

## Program Structure
The program consists of a single `main()` function that handles all game logic. It uses a nested loop structure to manage gameplay and replay functionality.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```
- `stdio.h`: Provides input/output functions like `printf()` and `scanf()`
- `stdlib.h`: Contains random number generation functions `rand()` and `srand()`
- `time.h`: Used to seed the random number generator with current time

### Variables
```c
int number, guess, attempts = 0;
char playAgain;
```
- `number`: Stores the randomly generated number the player needs to guess
- `guess`: Stores the player's current guess
- `attempts`: Counter for tracking the number of guesses (initialized to 0)
- `playAgain`: Character to store player's choice to play again

### Random Number Generation
```c
srand(time(0));
number = (rand() % 100) + 1;
```
- `srand(time(0))`: Seeds the random number generator with the current time to ensure different sequences on each run
- `rand() % 100`: Generates a random number between 0-99
- `(rand() % 100) + 1`: Adjusts the range to 1-100

### Main Game Loop
The program uses two nested `do-while` loops:
1. Outer loop: Controls replay functionality
2. Inner loop: Handles the guessing process for a single game

#### Guess Validation Logic
```c
if (guess > number) {
    printf("Too high! Try again.\n");
} else if (guess < number) {
    printf("Too low! Try again.\n");
} else {
    printf("Congratulations! You guessed the number in %d attempts!\n", attempts);
}
```
This conditional block compares the player's guess to the target number and provides appropriate feedback.

### Input Handling
```c
scanf("%d", &guess);
scanf(" %c", &playAgain);
```
- `%d`: Reads an integer for the player's guess
- `" %c"`: Reads a character for the play again decision (note the space before `%c` to consume any leftover newline characters)

## Program Flow
1. Welcome message is displayed
2. Outer loop begins (allows replay)
3. Random number is generated
4. Player is prompted for guesses
5. Each guess is evaluated and feedback is provided
6. Game continues until correct guess is made
7. Player is asked if they want to play again
8. If yes, repeat from step 3; if no, exit program

## Learning Points
1. **Random Number Generation**: Proper seeding technique using `time(0)`
2. **Loop Control**: Using nested loops for different game states
3. **Conditional Logic**: Implementing decision-making with `if-else if-else`
4. **Input/Output Handling**: Managing user input with proper format specifiers
5. **Variable Scope**: Understanding how variables persist across loops