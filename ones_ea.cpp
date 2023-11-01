// SIMPLE EA WITH CROSSOVER AND MUTATION WITH REPLACE WORST SOLUTION TO FIND A SOLUTION WITH ALL 1s
// STARTING WITH A RANDOM POPULATION OF CANDIDATES.

#include "ones_ea.h"

float MUT_RATE  = 0.8;
float CROSSOVER_RATE = 0.8;
int POP_SIZE = 10;
int SOLUTION_LENGTH = 10;
int TOURNAMENT_SIZE = 4;
int GENERATIONS = 50;

int main()
{
    int pop_size, solution_length;
    srand(time(0));

    int** pop = generate_random_pop(POP_SIZE, SOLUTION_LENGTH);
    std::cout << "ORIGINAL POPULATION:" << std::endl;
    output_population(pop, POP_SIZE, SOLUTION_LENGTH);


    int i, j;
    for(i = 0; i < GENERATIONS; i++)
    {
        int* parent1 = play_tournament(pop, POP_SIZE, SOLUTION_LENGTH, TOURNAMENT_SIZE);
        int* parent2 = play_tournament(pop, POP_SIZE, SOLUTION_LENGTH, TOURNAMENT_SIZE);

        // crossover to create two children
        int** children = crossover(parent1, parent2, SOLUTION_LENGTH, CROSSOVER_RATE);

        for(j = 0; j < 2; j++)
        {
            bit_mutation(children[j], SOLUTION_LENGTH, MUT_RATE);

            // replace mutated tournament winner only if better than worst solution
            int replaced = replace_worst_solution(pop, POP_SIZE, SOLUTION_LENGTH, children[j]);
            if(!replaced)
                delete[] children[j];
        }
        delete[] children;
        
        // find the best solution and break if that solution fitness is optimal
        int best = 0;
        for(j = 1; j < POP_SIZE; j++)
        {
            if(solution_fitness(pop[j], SOLUTION_LENGTH) > solution_fitness(pop[best], SOLUTION_LENGTH))
                best = j;
        }

        printf("ITERATION: %d\tPOPULATION FITNESS: %d\tBEST SOLUTION FITNESS: %d\n", i, population_fitness(pop, POP_SIZE, SOLUTION_LENGTH), solution_fitness(pop[best], SOLUTION_LENGTH));

        if(solution_fitness(pop[best], SOLUTION_LENGTH) == SOLUTION_LENGTH)
            break;
    }
    
    std::cout << "Optimal solution found after " << i + 1 << " iterations !" << std::endl;
    return 0;
}

