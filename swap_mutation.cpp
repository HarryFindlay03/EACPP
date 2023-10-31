#include <iostream>
#include <cstdlib>

void swap_mutation(int*, int);

int main()
{
    srand(time(0));

    int sol[] = {1, 2, 3, 4, 5};
    swap_mutation(sol, 5);

    int i;
    for(i = 0; i < 5; i++)
        std::cout << sol[i];
    std::cout << std::endl;
    return 0;
}

void swap_mutation(int* solution, int solution_length)
{
    int pos1 = rand() % solution_length;
    int pos2 = rand() % solution_length;

    int temp = solution[pos1];
    solution[pos1] = solution[pos2];
    solution[pos2] = temp;

    return;
}
