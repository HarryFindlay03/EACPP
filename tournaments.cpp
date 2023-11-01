#include "tournaments.h"

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

int* tsp_get_tournament_winner(int** pool, int tournament_size, int solution_length, int** map)
{
    int i;
    int* temp_res = new int[tournament_size];
    for(i = 0; i < tournament_size; i++)
        temp_res[i] = tsp_solution_fitness(map, solution_length, pool[i]);
    
    int best_pos = 0;
    for(i = 1; i < tournament_size; i++)
        if(temp_res[i] < temp_res[best_pos])
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

int* tsp_play_tournament(int** map, int** pop, int pop_size, int solution_length, int tournament_size)
{
    int** pool = create_tournament_pool(pop, pop_size, tournament_size);
    int* tournament_winner = tsp_get_tournament_winner(pool, tournament_size, solution_length, map);

    delete[] pool;
    return tournament_winner;
}
