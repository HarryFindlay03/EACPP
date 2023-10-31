#include <iostream>
#include <cstdlib>

int** ordered_crossover(int*, int*, int);
void partial_ordered_child(int*, int*, int*, int, int);

int main()
{
    srand(time(0));

    int parent1[] = {0, 3, 4, 2, 1};
    int parent2[] = {1, 4, 2, 3, 0};

    // outputting parent1 and parent2
    int i, j;
    std::cout << "parent1: ";
    for(i = 0; i < 5; i++)
        std::cout << parent1[i];
    std::cout << std::endl << "parent2: ";
    for(i = 0; i < 5; i++)
        std::cout << parent2[i];
    std::cout << std::endl;


    int** children = ordered_crossover(parent1, parent2, 5);

    for(i = 0; i < 2; i++)
    {
        int* child = children[i];
        for(j = 0; j < 5; j++)
        {
            std::cout << *child++;
        }
        std::cout << std::endl;
    }
    
    return 0;
}

int** ordered_crossover(int* parent1, int* parent2, int solution_length)
{
    // p1: 03421
    // p2: 14230
    // c1: 03142
    // c2: 14032

    int** pool = new int*[2];
    int* child1 = new int[solution_length];
    int* child2 = new int[solution_length];

    int i, j;
    int crossover_point = rand() % solution_length;
    std::cout << "crossover point: " << crossover_point << std::endl;
    for(i = 0; i < crossover_point; i++)
    {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }
    
    // filling remaining spots in both children
    partial_ordered_child(child1, parent1, parent2, solution_length, crossover_point);
    partial_ordered_child(child2, parent2, parent1, solution_length, crossover_point);

    pool[0] = child1;
    pool[1] = child2;

    return pool;
}

void partial_ordered_child(int* partial_child, int* parent1, int* parent2, int solution_length, int crossover_point)
{
    // find remaining
    int i, j;
    int* remaining = new int[solution_length - crossover_point];
    for(i = crossover_point; i < solution_length; i++)
    {
        remaining[i - crossover_point] = parent1[i]; 
    }

    // go through parent and add order of what is in remaining in parent to child
    partial_child += crossover_point;
    for(i = 0; i < solution_length; i++)
    {
        // if parent[i] in remaining
        for(j = 0; j < solution_length - crossover_point; j++)
        {
            if(parent2[i] == remaining[j])
                *partial_child++ = parent2[i];
        }
    }

    delete[] remaining;
}
