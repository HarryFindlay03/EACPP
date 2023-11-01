#include "tsp_functions.h"

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
