#include "tsp_ea.h"

int POPULATION_SIZE = 10;

int main()
{
    int n = 5;
    
    // initialising the map
    int zero[]  = {0, 4, 9, 8, 2};
    int one[] = {4, 0, 3, 5, 4};
    int two[] = {9, 3, 0, 11, 16};
    int three[] = {8, 5, 11, 0, 1};
    int four[] = {2, 4, 16, 1, 0};

    int** map = new int*[5];
    map[0] = zero;
    map[1] = one;
    map[2] = two;
    map[3] = three;
    map[4] = four;

    int i, j;
    std::cout << "MAP" << std::endl;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%3d", map[i][j]);
        std::cout << std::endl;
    }

    // generate random tsp population
    int** pop = generate_random_tsp_population(POPULATION_SIZE, n);
    std::cout << "Random population!" << std::endl;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%d", pop[i][j]);
        std::cout << std::endl;
    }


    return 0;
}
