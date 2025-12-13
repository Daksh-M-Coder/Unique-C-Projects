#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define POPULATION_SIZE 100
#define CHROMOSOME_LENGTH 20
#define MAX_GENERATIONS 1000
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 0.8
#define TOURNAMENT_SIZE 5

// Chromosome structure
typedef struct {
    int genes[CHROMOSOME_LENGTH];
    double fitness;
} Chromosome;

// Population structure
typedef struct {
    Chromosome individuals[POPULATION_SIZE];
    double total_fitness;
    double best_fitness;
    double average_fitness;
    int best_individual_index;
} Population;

// Function prototypes
void initialize_population(Population* pop);
void initialize_chromosome(Chromosome* chrom);
void calculate_fitness(Chromosome* chrom);
void evaluate_population(Population* pop);
void tournament_selection(Population* pop, Chromosome* parent1, Chromosome* parent2);
void crossover(Chromosome* parent1, Chromosome* parent2, Chromosome* offspring1, Chromosome* offspring2);
void mutate(Chromosome* chrom);
void replace_population(Population* current_pop, Population* new_pop);
void print_chromosome(Chromosome* chrom);
void print_population_stats(Population* pop, int generation);

// Initialize a chromosome with random genes
void initialize_chromosome(Chromosome* chrom) {
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        chrom->genes[i] = rand() % 2; // Random binary gene (0 or 1)
    }
    calculate_fitness(chrom);
}

// Initialize the entire population
void initialize_population(Population* pop) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        initialize_chromosome(&pop->individuals[i]);
    }
    evaluate_population(pop);
}

// Fitness function - example: count the number of 1s in the chromosome
// In a real application, this would be problem-specific
void calculate_fitness(Chromosome* chrom) {
    // Example fitness function: maximize the number of 1s
    chrom->fitness = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        chrom->fitness += chrom->genes[i];
    }
    
    // Alternative fitness function: try to match a target pattern
    // Uncomment the following section to use a target pattern instead
    /*
    double target_pattern[CHROMOSOME_LENGTH] = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0};
    chrom->fitness = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        if (chrom->genes[i] == (int)target_pattern[i]) {
            chrom->fitness += 1;
        }
    }
    */
}

// Evaluate the entire population
void evaluate_population(Population* pop) {
    pop->total_fitness = 0;
    pop->best_fitness = -1;
    pop->best_individual_index = 0;
    
    for (int i = 0; i < POPULATION_SIZE; i++) {
        calculate_fitness(&pop->individuals[i]);
        pop->total_fitness += pop->individuals[i].fitness;
        
        if (pop->individuals[i].fitness > pop->best_fitness) {
            pop->best_fitness = pop->individuals[i].fitness;
            pop->best_individual_index = i;
        }
    }
    
    pop->average_fitness = pop->total_fitness / POPULATION_SIZE;
}

// Tournament selection
void tournament_selection(Population* pop, Chromosome* parent1, Chromosome* parent2) {
    Chromosome tournament_pool[TOURNAMENT_SIZE];
    
    // Select individuals for tournament
    for (int i = 0; i < TOURNAMENT_SIZE; i++) {
        int random_index = rand() % POPULATION_SIZE;
        tournament_pool[i] = pop->individuals[random_index];
    }
    
    // Find the best in tournament for parent1
    int best_index = 0;
    for (int i = 1; i < TOURNAMENT_SIZE; i++) {
        if (tournament_pool[i].fitness > tournament_pool[best_index].fitness) {
            best_index = i;
        }
    }
    *parent1 = tournament_pool[best_index];
    
    // Select another parent (could be same as first)
    for (int i = 0; i < TOURNAMENT_SIZE; i++) {
        int random_index = rand() % POPULATION_SIZE;
        tournament_pool[i] = pop->individuals[random_index];
    }
    
    best_index = 0;
    for (int i = 1; i < TOURNAMENT_SIZE; i++) {
        if (tournament_pool[i].fitness > tournament_pool[best_index].fitness) {
            best_index = i;
        }
    }
    *parent2 = tournament_pool[best_index];
}

// Crossover operation (single point)
void crossover(Chromosome* parent1, Chromosome* parent2, Chromosome* offspring1, Chromosome* offspring2) {
    // Copy parents to offspring
    *offspring1 = *parent1;
    *offspring2 = *parent2;
    
    // Perform crossover with a certain probability
    if ((double)rand() / RAND_MAX < CROSSOVER_RATE) {
        int crossover_point = rand() % CHROMOSOME_LENGTH;
        
        // Swap genes after crossover point
        for (int i = crossover_point; i < CHROMOSOME_LENGTH; i++) {
            int temp = offspring1->genes[i];
            offspring1->genes[i] = offspring2->genes[i];
            offspring2->genes[i] = temp;
        }
        
        // Recalculate fitness for offspring
        calculate_fitness(offspring1);
        calculate_fitness(offspring2);
    }
}

// Mutation operation
void mutate(Chromosome* chrom) {
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            chrom->genes[i] = 1 - chrom->genes[i]; // Flip bit
        }
    }
    calculate_fitness(chrom);
}

// Replace current population with new population
void replace_population(Population* current_pop, Population* new_pop) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        current_pop->individuals[i] = new_pop->individuals[i];
    }
    current_pop->total_fitness = new_pop->total_fitness;
    current_pop->best_fitness = new_pop->best_fitness;
    current_pop->average_fitness = new_pop->average_fitness;
    current_pop->best_individual_index = new_pop->best_individual_index;
}

// Print chromosome information
void print_chromosome(Chromosome* chrom) {
    printf("Genes: ");
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        printf("%d", chrom->genes[i]);
    }
    printf(" | Fitness: %.2f\n", chrom->fitness);
}

// Print population statistics
void print_population_stats(Population* pop, int generation) {
    printf("Generation %d: Best=%.2f, Average=%.2f\n", 
           generation, pop->best_fitness, pop->average_fitness);
}

// Example objective function: find the maximum of a mathematical function
// This is an alternative to the binary counting fitness function
double objective_function(double x) {
    // Example: Find maximum of f(x) = x * sin(10 * pi * x) + 1.0
    // Domain: x in [0, 1]
    return x * sin(10 * M_PI * x) + 1.0;
}

// Convert binary chromosome to real value in [0,1]
double chromosome_to_real(Chromosome* chrom) {
    double value = 0;
    double power = 1;
    
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        value += chrom->genes[i] * power;
        power *= 2;
    }
    
    return value / (power - 1); // Normalize to [0,1]
}

// Real-valued fitness function
void calculate_real_fitness(Chromosome* chrom) {
    double x = chromosome_to_real(chrom);
    chrom->fitness = objective_function(x);
}

int main() {
    printf("Genetic Algorithm Framework\n");
    printf("==========================\n");
    printf("This program demonstrates a genetic algorithm that evolves a population\n");
    printf("to maximize the number of 1s in a binary chromosome.\n\n");
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Initialize population
    Population current_population;
    Population new_population;
    
    initialize_population(&current_population);
    
    printf("Initial population statistics:\n");
    print_population_stats(&current_population, 0);
    printf("Best individual: ");
    print_chromosome(&current_population.individuals[current_population.best_individual_index]);
    
    // Evolution loop
    for (int generation = 1; generation <= MAX_GENERATIONS; generation++) {
        // Create new population
        for (int i = 0; i < POPULATION_SIZE; i += 2) {
            // Selection
            Chromosome parent1, parent2;
            tournament_selection(&current_population, &parent1, &parent2);
            
            // Crossover
            Chromosome offspring1, offspring2;
            crossover(&parent1, &parent2, &offspring1, &offspring2);
            
            // Mutation
            mutate(&offspring1);
            mutate(&offspring2);
            
            // Add to new population
            new_population.individuals[i] = offspring1;
            if (i + 1 < POPULATION_SIZE) {
                new_population.individuals[i + 1] = offspring2;
            }
        }
        
        // Evaluate new population
        evaluate_population(&new_population);
        
        // Replace current population
        replace_population(&current_population, &new_population);
        
        // Print statistics every 100 generations
        if (generation % 100 == 0) {
            print_population_stats(&current_population, generation);
        }
        
        // Check for convergence (all genes are 1)
        if (current_population.best_fitness == CHROMOSOME_LENGTH) {
            printf("\nSolution found at generation %d!\n", generation);
            break;
        }
    }
    
    printf("\nFinal population statistics:\n");
    print_population_stats(&current_population, MAX_GENERATIONS);
    printf("Best individual: ");
    print_chromosome(&current_population.individuals[current_population.best_individual_index]);
    
    printf("\nGenetic Algorithm completed.\n");
    
    return 0;
}