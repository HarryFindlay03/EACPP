#include "mutations.h"

void swap_mutation(int* solution, int solution_length, float mutation_rate)
{
    float ran = (float)rand() / (float)RAND_MAX;

    if(mutation_rate > ran)
    {
        int pos1 = rand() % solution_length;
        int pos2 = rand() % solution_length;

        int temp = solution[pos1];
        solution[pos1] = solution[pos2];
        solution[pos2] = temp;
    }

    return;
}

void bit_mutation(int* solution, int solution_length, float mut_rate)
{
    int mutation_pos = rand() % solution_length;
    
    float ran = (float)rand() / (float)RAND_MAX;
    
    if(mut_rate > ran)
    {
        int* curr = solution + mutation_pos;
        *curr == 1 ? *curr = 0 : *curr = 1;
    }

    return;
}
