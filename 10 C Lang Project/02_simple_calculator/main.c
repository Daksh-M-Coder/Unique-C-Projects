#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototypes
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double power(double a, double b);
double square_root(double a);

void print_menu();

int main() {
    int choice;
    double num1, num2, result;
    char continue_calc;

    printf("Welcome to the Simple Calculator!\n");

    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Addition
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = add(num1, num2);
                printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 2: // Subtraction
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = subtract(num1, num2);
                printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 3: // Multiplication
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = multiply(num1, num2);
                printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 4: // Division
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                if (num2 != 0) {
                    result = divide(num1, num2);
                    printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
                } else {
                    printf("Error: Division by zero is not allowed!\n");
                }
                break;

            case 5: // Power
                printf("Enter base and exponent: ");
                scanf("%lf %lf", &num1, &num2);
                result = power(num1, num2);
                printf("%.2lf ^ %.2lf = %.2lf\n", num1, num2, result);
                break;

            case 6: // Square Root
                printf("Enter a number: ");
                scanf("%lf", &num1);
                if (num1 >= 0) {
                    result = square_root(num1);
                    printf("Square root of %.2lf = %.2lf\n", num1, result);
                } else {
                    printf("Error: Cannot calculate square root of a negative number!\n");
                }
                break;

            case 7: // Exit
                printf("Thank you for using the calculator!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &continue_calc);
        printf("\n");

    } while (continue_calc == 'y' || continue_calc == 'Y');

    return 0;
}

// Function definitions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

double power(double a, double b) {
    return pow(a, b);
}

double square_root(double a) {
    return sqrt(a);
}

void print_menu() {
    printf("\n===== Simple Calculator =====\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Power (^)\n");
    printf("6. Square Root (√)\n");
    printf("7. Exit\n");
    printf("=============================\n");
}