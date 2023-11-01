#include "ea_driver.h"
#include <algorithm>

int** generate_random_tsp_population(int, int);
int tsp_solution_fitness(int**, int, int*);
int tsp_population_fitness(int**, int, int, int**);
int tsp_replace_worst_solution(int**, int, int, int*, int**);
