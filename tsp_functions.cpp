#include "tsp_functions.h"
#include <random>

int** generate_random_tsp_population(int population_size, int solution_length)
{
    int** pop = new int*[population_size];

    std::default_random_engine g = std::default_random_engine(time(0));

    int i, j;
    for(i = 0; i < population_size; i++)
    {
        pop[i] = new int[solution_length];
        for(j = 0; j < solution_length; j++)
        {
            pop[i][j] = j;
        }
            
        // shuffling array using random engine generated earlier
        std::shuffle(pop[i], pop[i] + solution_length - 1, g);
    }
    return pop;
}

int tsp_solution_fitness(int** map, int n, int* solution)
{
    int res = 0;
    int i;
    for(i = 0; i < n - 1; i++)
        res += (map[solution[i]][solution[i+1]]);
    // adding circular distance
    res += map[solution[n-1]][solution[0]];

    return res;
}

int tsp_population_fitness(int** map, int population_size, int solution_length, int** pop)
{
    int res = 0;
    int i;
    for(i = 0; i < population_size; i++)
        res += tsp_solution_fitness(map, solution_length, pop[i]);

    return res;
}

int tsp_replace_worst_solution(int** pop, int population_size, int solution_length, int* new_solution, int** map)
{
    // funtion returns true or false depending on whether solution was replaced
    int res = 0;

    // get the position of the worst solution
    int worst = 0;
    int i;
    for(i = 1; i < population_size; i++)
        if(tsp_solution_fitness(map, solution_length, pop[i]) > tsp_solution_fitness(map, solution_length, pop[worst]))
            worst = i;
    
    // replace the worst solution with the new better solution only if better solution is better
    if(tsp_solution_fitness(map, solution_length, new_solution) < tsp_solution_fitness(map, solution_length, pop[worst]))
    {
        delete[] pop[worst];
        pop[worst] = new_solution;
        res = 1;
    }
    
    return res;
}

