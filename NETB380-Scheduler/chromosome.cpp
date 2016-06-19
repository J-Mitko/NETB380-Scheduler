#include "chromosome.h"
#include <math.h>

int MAXGENS = 10;

Chromosome::Chromosome(Schedule init_schedule)
{
    srand(unsigned(time(0)));

}

Chromosome::~Chromosome()
{}

void Chromosome::selector()
{
    int total_fitness;
    double a = 0.0;
    double b = 1.0;
    double x;

    //  Find the total fitness of the population.
    for(int i = 0;i < MAXGENS; i++)
    {
        total_fitness += gene[i].get_fitness();
    }
    //  Calculate the relative fitness of each member.
    for(int i = 0; i < MAXGENS; i++)
    {
        gene[i].set_relative_fitness( gene[i].get_fitness() / total_fitness );
    }
    //  Calculate the cumulative fitness.
    for(int i = 1; i < MAXGENS; i++)
    {
        gene[i].set_cumulative_fitness( gene[i-1].get_cumulative_fitness() + gene[i].get_relative_fitness() );
    }
    //  Select survivors using cumulative fitness.
    for(int i = 0; i < MAXGENS; i++)
    {
        x = rng_ab(a,b);
        if( x < gene[0].get_cumulative_fitness())
        {
           // newGene[i] = gene[0];
        }
        else
        {
            for(int j = 0; j< MAXGENS; j++)
            {
                if( gene[j].get_cumulative_fitness() <= x && x < gene[j+1].get_cumulative_fitness())
                {
                    //newGene[i] = gene[j+1];
                }
            }
        }
    }
    //  Overwrite the old population with the new one.
    for(int i = 0; i < MAXGENS; i++)
    {
        //gene[i] = newGene[i];
    }

}

void Chromosome::mutate()
{
    int lowest_fitness;
    int current_fitness;
    int leakest;// get index of leakest
    int x;

    lowest_fitness = gene[0].get_fitness();

    for(int mut = 0; mut <= MAXGENS * 20 /100; mut++)// perform only on 20% of the population
    {

        for(int i = 0;i < MAXGENS; i++)// finds leakest in the one
        {
            current_fitness = gene[i].get_fitness();
            if(current_fitness < lowest_fitness)
            {
                lowest_fitness = current_fitness;
                leakest = i;
            }
        }
        x = rng_i(10);
        if(x < MUTATION)
        {
            gene[leakest].randomize_schedule();
        }
    }

}

int Chromosome::rng_i(int i)
{
    return rand() % i + 1;
}
double Chromosome::rng_ab(double a, double b)
{
    return fmod((double)rand(), a + b);
}


