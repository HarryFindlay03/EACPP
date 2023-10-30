#include <iostream>
#include <cstdlib>
#include <ctime>

int** generate_random_pop(int, int);
void mutation(int*, int, float);
int** crossover(int*, int*, int, float);
int** create_tournament_pool(int**, int, int);
int* get_tournament_winner(int**, int, int);
int* play_tournament(int**, int, int, int);
int solution_fitness(int*, int);
int population_fitness(int**, int, int);
int replace_worst_solution(int**, int, int, int*);

void output_population(int**, int, int);
