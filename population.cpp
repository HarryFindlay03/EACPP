#include "population.h"

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
