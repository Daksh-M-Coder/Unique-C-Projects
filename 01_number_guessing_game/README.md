# Number Guessing Game

## Description
A classic number guessing game where the computer generates a random number between 1 and 100, and the player tries to guess it. The game provides feedback on whether each guess is too high or too low and keeps track of the number of attempts.

## Features
- Random number generation between 1 and 100
- Attempt counter
- Play again functionality
- User-friendly prompts and feedback

## Standard Library Functions Used
- `stdio.h` - For input/output operations (`printf`, `scanf`)
- `stdlib.h` - For random number generation (`rand`, `srand`)
- `time.h` - For seeding the random number generator (`time`)

## How to Compile and Run

### Compilation
```bash
gcc -o number_guessing main.c
```

### Execution
```bash
./number_guessing
```

On Windows:
```bash
number_guessing.exe
```

## How to Play
1. Run the program
2. The computer will generate a random number between 1 and 100
3. Enter your guess when prompted
4. Receive feedback on whether your guess was too high or too low
5. Continue guessing until you find the correct number
6. After winning, choose whether to play again or quit

## Sample Output
```
Welcome to the Number Guessing Game!

I'm thinking of a number between 1 and 100.
Can you guess what it is?
Enter your guess: 50
Too high! Try again.
Enter your guess: 25
Too low! Try again.
Enter your guess: 37
Too high! Try again.
Enter your guess: 31
Congratulations! You guessed the number in 4 attempts!

Would you like to play again? (y/n): n
Thanks for playing!
```