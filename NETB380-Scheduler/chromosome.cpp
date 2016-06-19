#include "chromosome.h"
#include <math.h>

int SIZE = 10;
int MUTATION = 2;
double PXOVER = 0.8;

Chromosome::Chromosome()
{
    srand(unsigned(time(0)));
    for(int i = 0;i< SIZE;i++)
    {
        //chromosomes.push_back(init_schedule);
    }
}

Chromosome::~Chromosome()
{}

void Chromosome::selector() //SEGMENT FAULT
{
    int total_fitness;
    double a = 0.0;
    double b = 1.0;
    double x;

    //  Find the total fitness of the population.
    for(int i = 0;i < SIZE; i++)
    {
        total_fitness += chromosomes[i].get_fitness();
    }
    //  Calculate the relative fitness of each member.
    for(int i = 0; i < SIZE; i++)
    {
        chromosomes[i].set_relative_fitness( chromosomes[i].get_fitness() / total_fitness );
    }
    //  Calculate the cumulative fitness.
    for(int i = 1; i < SIZE; i++)
    {
        chromosomes[i].set_cumulative_fitness( chromosomes[i-1].get_cumulative_fitness() + chromosomes[i].get_relative_fitness() );
    }
    //  Select survivors using cumulative fitness.
    for(int i = 0; i < SIZE; i++)
    {
        x = rng_ab(a,b);
        if( x < chromosomes[0].get_cumulative_fitness())
        {
           newSequence[i] = chromosomes[0];
        }
        else
        {
            for(int j = 0; j< SIZE; j++)
            {
                if( chromosomes[j].get_cumulative_fitness() <= x && x < chromosomes[j+1].get_cumulative_fitness())
                {
                    newSequence[i] = chromosomes[j+1];
                }
            }
        }
    }
    //  Overwrite the old population with the new one.
    for(int i = 0; i < SIZE; i++)
    {
        chromosomes[i] = newSequence[i];
    }

}

void Chromosome::mutate()
{
    int lowest_fitness;
    int current_fitness;
    int leakest;// get index of leakest
    int x;

    lowest_fitness = chromosomes[0].get_fitness();

    for(int mut = 0; mut <= SIZE * 20 /100; mut++)// perform only on 20% of the population
    {

        for(int i = 0;i < SIZE; i++)// finds leakest in the one
        {
            current_fitness = chromosomes[i].get_fitness();
            if(current_fitness < lowest_fitness)
            {
                lowest_fitness = current_fitness;
                leakest = i;
            }
        }
        x = rng_i(10);
        if(x < MUTATION)
        {
            chromosomes[leakest].randomize_schedule();
        }
    }

}

void Chromosome::crossover() // TEST!!!
{
    const double a = 0.0;
    const double b = 1.0;
    int timeslot_1 = 0;
    int timeslot_2 = 1;
    int index = 0;//chomosome index

    double x;

    for(int i = 0;i<SIZE;i++)
    {
        x = rng_ab(a,b);
        index = rng_i(SIZE);//get random index

        if(x < PXOVER)//time slot < 36
        {
            if(timeslot_1 < 36 && timeslot_2 < 36)
            {
                timeslot_1++;
                if(timeslot_1 % 2 == 0)
                {
                    Xover(index,timeslot_1,timeslot_2);
                }
                else
                {
                    timeslot_2++;
                }
            }
            else
                break;
        }
    }
}
void Chromosome::Xover(int index, int timeslot_1, int timeslot_2)
{
    chromosomes[index].swap_timeslots(timeslot_1,timeslot_2);
}



int Chromosome::rng_i(int i)
{
    return rand() % i + 1;
}
double Chromosome::rng_ab(double a, double b)
{
    return fmod((double)rand(), a + b);
}


