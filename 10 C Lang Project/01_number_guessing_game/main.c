#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;
    char playAgain;

    printf("Welcome to the Number Guessing Game!\n");
    
    do {
        // Seed the random number generator
        srand(time(0));
        number = (rand() % 100) + 1;  // Generate random number between 1 and 100
        attempts = 0;
        
        printf("\nI'm thinking of a number between 1 and 100.\n");
        printf("Can you guess what it is?\n");
        
        do {
            printf("Enter your guess: ");
            scanf("%d", &guess);
            attempts++;
            
            if (guess > number) {
                printf("Too high! Try again.\n");
            } else if (guess < number) {
                printf("Too low! Try again.\n");
            } else {
                printf("Congratulations! You guessed the number in %d attempts!\n", attempts);
            }
        } while (guess != number);
        
        printf("\nWould you like to play again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');
    
    printf("Thanks for playing!\n");
    return 0;
}