#include "ea_driver.h"
#include "population.h"
#include "tsp_functions.h"

int** create_tournament_pool(int**, int, int);
int* get_tournament_winner(int**, int, int);
int* play_tournament(int**, int, int, int);

int* tsp_get_tournament_winner(int**, int, int, int**);
int* tsp_play_tournament(int** ,int**, int, int, int);
