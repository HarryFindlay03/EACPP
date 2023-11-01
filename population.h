#include "ea_driver.h"

int** generate_random_pop(int, int);
int solution_fitness(int*, int);
int population_fitness(int**, int, int);
int replace_worst_solution(int**, int, int, int*);

void output_population(int**, int, int);
