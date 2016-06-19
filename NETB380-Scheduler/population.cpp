#include "population.h"
#include <vector>
#include <math.h>

int POPULATION_SIZE = 10;
int MAXGENS = 100;
int NVARS = 6;// FOR SIX DAYS
int MUTATION = 2;// mutation chance 1-10

Population::Population(Schedule& init_schedule)
{
    srand(unsigned(time(0)));
    for(int i = 0;i< POPULATION_SIZE;i++)
    {
        population.push_back(init_schedule);
    }
}

Population::~Population()
{}


void Population::elitist()
{

}

void Population::selector()
{
    int total_fitness;
    double a = 0.0;
    double b = 1.0;
    double x;

    //  Find the total fitness of the population.
    for(int i = 0;i < POPULATION_SIZE; i++)
    {
        total_fitness += population[i].get_fitness();
    }
    //  Calculate the relative fitness of each member.
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        population[i].set_relative_fitness( population[i].get_fitness() / total_fitness );
    }
    //  Calculate the cumulative fitness.
    for(int i = 1; i < POPULATION_SIZE; i++)
    {
        population[i].set_cumulative_fitness( population[i-1].get_cumulative_fitness() + population[i].get_relative_fitness() );
    }
    //  Select survivors using cumulative fitness.
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        x = rng_ab(a,b);
        if( x < population[0].get_cumulative_fitness())
        {
            newPopulation[i] = population[0];
        }
        else
        {
            for(int j = 0; j< POPULATION_SIZE; j++)
            {
                if( population[j].get_cumulative_fitness() <= x && x < population[j+1].get_cumulative_fitness())
                {
                    newPopulation[i] = population[j+1];
                }
            }
        }
    }
    //  Overwrite the old population with the new one.
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        population[i] = newPopulation[i];
    }

}

void Population::mutate()
{
    int lowest_fitness;
    int current_fitness;
    int leakest;// get index of leakest
    int x;

    lowest_fitness = population[0].get_fitness();

    for(int mut = 0; mut <= POPULATION_SIZE * 20 /100; mut++)// perform only on 20% of the population
    {

        for(int i = 0;i < POPULATION_SIZE; i++)// finds leakest in the one
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
    return rand() % i + 1;
}
double Population::rng_ab(double a, double b)
{
    return fmod((double)rand(), a + b);
}


