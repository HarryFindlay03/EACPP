#include "tsp_ea.h"

float MUT_RATE  = 0.8;
float CROSSOVER_RATE = 0.8;
int POPULATION_SIZE = 10;
int TOURNAMENT_SIZE = 4;
int GENERATIONS = 50;

int main()
{
    // seeding rand
    srand(time(0));

    int n = 5;
    
    // initialising the map
    int zero[]  = {0, 44, 109, 88, 200};
    int one[] = {44, 0, 53, 65, 404};
    int two[] = {109, 53, 0, 11, 16};
    int three[] = {88, 65, 11, 0, 1000};
    int four[] = {200, 404, 16, 1000, 0};

    int** map = new int*[5];
    map[0] = zero;
    map[1] = one;
    map[2] = two;
    map[3] = three;
    map[4] = four;
    
    int** pop = generate_random_tsp_population(POPULATION_SIZE, n);

    int i, j;
    for(i = 0; i < GENERATIONS; i++)
    {
        int* parent1 = tsp_play_tournament(map, pop, POPULATION_SIZE, n, TOURNAMENT_SIZE);
        int* parent2 = tsp_play_tournament(map, pop, POPULATION_SIZE, n, TOURNAMENT_SIZE);

        int** children = ordered_crossover(parent1, parent2, n);

        for(j = 0; j < 2; j++)
        {
            swap_mutation(children[j], n, MUT_RATE);

            //replace mutated tournament winner only if better than the worst solution
            int replaced = tsp_replace_worst_solution(pop, POPULATION_SIZE, n, children[j], map);
            if(!replaced)
                delete[] children[j];
        }
        delete[] children;

        int best = 0;
        for(j = 1; j < POPULATION_SIZE; j++)
        {
            if(tsp_solution_fitness(map, n, pop[j]) > tsp_solution_fitness(map, n, pop[best]))
                best = j;
        }

        printf("ITERATION: %d\tPOPULATION FITNESS: %d\tBEST SOLUTION FITNESS: %d\t", i, tsp_population_fitness(map, POPULATION_SIZE, n, pop), tsp_solution_fitness(map, n, pop[best]));
        
        std::cout << "BEST SOLUTION: ";
        int x;
        for(x = 0; x < n; x++)
            std::cout << pop[best][x];
        std::cout << std::endl;
    }


    return 0;
}
