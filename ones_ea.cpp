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
            mutation(children[j], SOLUTION_LENGTH, MUT_RATE);

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

int** generate_random_pop(int pop_size, int solution_length)
{
    int** res = new int*[pop_size];
    
    int i, j;
    for(i = 0; i < pop_size; i++)
    {
        res[i] = new int[solution_length];
        for(j = 0; j < solution_length; j++)

            res[i][j] = rand() % 2;
    }

    return res;
}

void mutation(int* solution, int solution_length, float mut_rate)
{
    int mutation_pos = rand() % solution_length;
    
    float ran = (float)rand() / (float)RAND_MAX;
    
    if(mut_rate > ran)
    {
        int* curr = solution + mutation_pos;
        *curr == 1 ? *curr = 0 : *curr = 1;
    }
}

int** crossover(int* parent1, int* parent2, int solution_length, float crossover_rate)
{
    float ran = (float)rand() / (float)RAND_MAX;
    int crossover_point = rand() % solution_length;
    
    int* child1 = new int[solution_length];
    int* child2 = new int[solution_length];
    int i;

    
    // currently no crossover rate
    for(i = 0; i < crossover_point; i++)
    {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }
    for(;i < solution_length; i++)
    {
        child1[i] = parent2[i];
        child2[i] = parent1[i];
    }

    int** children = new int*[2];
    children[0] = child1;
    children[1] = child2;

    return children;
}

int** create_tournament_pool(int** pop, int pop_size, int tournament_size)
{
    int** pool = new int*[tournament_size];
    
    int i;
    for(i = 0; i < tournament_size; i++)
        pool[i] = pop[rand() % pop_size];

    return pool;
}

int* get_tournament_winner(int** pool, int tournament_size, int solution_length)
{
    int i;
    int* temp_res = new int[tournament_size];
    for(i = 0; i < tournament_size; i++)
        temp_res[i] = solution_fitness(pool[i], solution_length);
    
    int best_pos = 0;
    for(i = 1; i < tournament_size; i++)
        if(temp_res[i] > temp_res[best_pos])
            best_pos = i;
    
    delete[] temp_res;
    return pool[best_pos];
}

int* play_tournament(int** pop, int pop_size, int solution_length, int tournament_size)
{
    int** pool = create_tournament_pool(pop, pop_size, tournament_size);
    int* tournament_winner = get_tournament_winner(pool, tournament_size, solution_length);

    delete[] pool;
    return tournament_winner;
}

int replace_worst_solution(int** pop, int population_size, int solution_length, int* new_solution)
{
    // funtion returns true or false depending on whether solution was replaced
    int res = 0;

    // get the position of the worst solution
    int worst = 0;
    int i;
    for(i = 1; i < population_size; i++)
        if(solution_fitness(pop[i], solution_length) < solution_fitness(pop[worst], solution_length))
            worst = i;
    
    // replace the worst solution with the new better solution only if better solution is better
    if(solution_fitness(new_solution, solution_length) > solution_fitness(pop[worst], solution_length))
    {
        delete[] pop[worst];
        pop[worst] = new_solution;
        res = 1;
    }
    
    return res;
}

int solution_fitness(int* solution, int solution_length)
{
    int i, res;
    res = 0;
    for(i = 0; i < solution_length; i++)
        if(solution[i] == 1)
            res++;

    return res;
}

int population_fitness(int** pop, int population_size, int solution_length)
{
    int res = 0;
    int i;
    for(i = 0; i < population_size; i++)
        res += solution_fitness(pop[i], solution_length);

    return res;
}

void output_population(int** pop, int pop_size, int sol_length)
{
    int i, j;
    for(i = 0; i < pop_size; i++)
    {
        for(j = 0; j < sol_length; j++)
            std::cout << pop[i][j];
        std::cout << std::endl;
    }
}
