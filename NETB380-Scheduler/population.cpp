#include "population.h"

int POPULATION_SIZE = 10;
int MAXGENS = 100;
int NVARS = 6;// FOR SIX DAYS
int MUTATION = 2;// mutation chance

Population::Population(Schedule init_schedule)
{
    srand(unsigned(time(0)));
    for(int i = 0;i< POPULATION_SIZE;i++)
    {
        this->population[i] = init_schedule;
    }
}

Population::~Population()
{}


void Population::elitist()
{

}

void Population::mutate()
{
    int lowest_fitness;
    int current_fitness;
    int leakest;// get index of leakest
    int x;

    lowest_fitness = population[0].get_fitness();

    for(int mut = 0; mut <= POPULATION_SIZE * 20 /100; mut++)// perfom only on 20% of the population
    {

        for(int i = 0;i < POPULATION_SIZE; i++)
        {
            current_fitness = population[i].get_fitness();
            if(current_fitness < lowest_fitness)
            {
                lowest_fitness = current_fitness;
                leakest = i;
            }
        }
        x = rng_i(10);
        if(x < MUTATION)
        {
            population[leakest].randomize_schedule();
        }
    }

}

int Population::rng_i(int i)
{
    return rand() % i;
}
int Population::rng_ab(int a, int b)
{
    return rand() % a + b;
}


