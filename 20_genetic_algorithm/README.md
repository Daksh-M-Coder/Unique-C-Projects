# Genetic Algorithm Framework

A flexible framework for implementing genetic algorithms to solve optimization problems.

## Description

This project implements a genetic algorithm framework that can be used to solve various optimization problems. Genetic algorithms are a type of evolutionary computation technique inspired by biological evolution, using mechanisms such as selection, crossover, and mutation to evolve solutions to problems over successive generations.

## Features

- Configurable population size and chromosome length
- Tournament selection mechanism
- Single-point crossover operation
- Bit-flip mutation operator
- Fitness evaluation framework
- Generation-based evolution process
- Population statistics tracking
- Convergence detection
- Extensible design for custom problems

## Compilation

To compile this project, use the following command:

```bash
gcc -o genetic_algorithm main.c -lm
```

Note: The `-lm` flag is required to link the math library.

## Usage

Run the program with:

```bash
./genetic_algorithm
```

The program will run a genetic algorithm to maximize the number of 1s in a binary chromosome. The evolution process will display statistics every 100 generations and stop when a solution is found or the maximum number of generations is reached.

## How Genetic Algorithms Work

### Basic Concepts

1. **Population**: A collection of candidate solutions (individuals)
2. **Chromosome**: A representation of a candidate solution
3. **Gene**: A single element of a chromosome
4. **Fitness**: A measure of how good a solution is
5. **Generation**: One iteration of the evolutionary process

### Evolutionary Process

1. **Initialization**: Create an initial random population
2. **Evaluation**: Calculate fitness for each individual
3. **Selection**: Choose parents based on fitness
4. **Crossover**: Combine parents to create offspring
5. **Mutation**: Introduce random changes in offspring
6. **Replacement**: Form new population from offspring
7. **Repeat**: Continue until termination condition is met

### Selection Mechanism

The framework uses tournament selection:
- Randomly select a subset of individuals (tournament)
- Choose the best individual from the tournament
- Repeat to select pairs of parents

### Crossover Operation

Single-point crossover is implemented:
- Select a random crossover point
- Exchange chromosome segments after the crossover point
- Create two new offspring from two parents

### Mutation Operation

Bit-flip mutation is used:
- For each gene, flip its value with a small probability
- Introduces genetic diversity in the population

## Configuration Options

The algorithm can be configured through constants:

- `POPULATION_SIZE`: Number of individuals in each generation
- `CHROMOSOME_LENGTH`: Length of each chromosome (number of genes)
- `MAX_GENERATIONS`: Maximum number of generations to run
- `MUTATION_RATE`: Probability of mutation for each gene
- `CROSSOVER_RATE`: Probability of crossover between parents
- `TOURNAMENT_SIZE`: Number of individuals in each tournament

## Example Problem

The default implementation solves the "Max Ones" problem:
- Objective: Maximize the number of 1s in a binary string
- Fitness: Count of 1s in the chromosome
- Solution: Chromosome with all genes set to 1

## Adapting to Other Problems

To solve different optimization problems:

1. Modify the `calculate_fitness` function to implement your objective function
2. Adjust chromosome representation if needed
3. Tune genetic operators and parameters for your problem
4. Implement problem-specific constraints if necessary

## Technical Details

### Data Structures

- **Chromosome**: Represents an individual solution with genes and fitness
- **Population**: Collection of individuals with statistics

### Algorithm Flow

1. Initialize random population
2. Evaluate all individuals
3. For each generation:
   - Select parents using tournament selection
   - Apply crossover to create offspring
   - Apply mutation to offspring
   - Evaluate offspring fitness
   - Replace population with offspring
   - Track statistics and check termination conditions

## Performance Considerations

1. **Population Size**: Larger populations explore more solutions but require more computation
2. **Chromosome Length**: Longer chromosomes can represent more complex solutions
3. **Mutation Rate**: Higher rates increase diversity but may disrupt good solutions
4. **Crossover Rate**: Higher rates increase exploitation of good solutions
5. **Tournament Size**: Larger tournaments increase selection pressure

## Possible Extensions

- Implement different selection mechanisms (roulette wheel, rank-based)
- Add multiple crossover operators (uniform, multi-point)
- Implement advanced mutation operators (swap, inversion)
- Add elitism to preserve best solutions
- Implement multi-objective optimization
- Add adaptive parameter control
- Implement parallel evaluation of fitness
- Add visualization of evolution process
- Support for different chromosome representations (real-valued, permutation)

## Requirements

- Standard C library
- Math library (`libm`)

## License

This project is released into the public domain.