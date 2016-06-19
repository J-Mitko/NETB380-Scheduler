#include "chromosome.h"
#include <math.h>

int SIZE = 10;
int MUTATION = 2;
double PXOVER = 0.8;

Chromosome::Chromosome(Schedule init_schedule)
{
    srand(unsigned(time(0)));
    for(int i = 0;i< SIZE;i++)
    {
        init_schedule.randomize_schedule();
        chromosomes.push_back(init_schedule);
        //call for first time fitness_calculation()
        chromosomes[i].fitness_calculation();
    }
}

Chromosome::~Chromosome()
{}

void Chromosome::selector()
{}

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

void Chromosome::evaluate()
{
    int best_fitness = 0;
    int best_chromosome_index;

    for(int i = 0;i<SIZE;i++)
    {
        if(best_fitness < chromosomes[i].get_fitness())
        {
            best_fitness = chromosomes[i].get_fitness();
            best_chromosome_index = i;
        }
    }

    if(prevSequence.empty())
    {
        for(int i = 0;i < SIZE;i++)
        {
            prevSequence.push_back(chromosomes[i]);//copy chromosomes
        }
    }
    else
    {
        for(int i = 0;i < SIZE;i++)
        {
            if(chromosomes[i].get_fitness() < prevSequence[i].get_fitness())
            {
                if(best_fitness < prevSequence[i].get_fitness())
                {
                    chromosomes[i] = prevSequence[i];
                    best_fitness = prevSequence[i].get_fitness();
                    best_chromosome_index = i;
                }
                else
                {
                    chromosomes[i] = prevSequence[i];
                }
            }
            else
            {
                prevSequence[i] = chromosomes[i];
            }
        }

        best_chromosome = chromosomes[best_chromosome_index];
    }
}

void Chromosome::report(int generation)
{
    double avg;
    int best_val = 0;
    int sum;
    if ( generation == 0 )
    {
        cout << "\n";
        cout << "  Generation       Best            Average  \n";
        cout << "  number           value           fitness  \n";
        cout << "\n";
    }

    for (int i=0; i<SIZE; i++)
    {
        sum += chromosomes[i].get_fitness();
        if(best_val < chromosomes[i].get_fitness())
        {
            best_val = chromosomes[i].get_fitness();
        }
    }

    avg = sum / (double)SIZE;

    cout << "  " << generation << "                 " << best_val << "                "<< avg <<"\n";
}

void Chromosome::print()
{
    best_chromosome.print_schedule();
}
int Chromosome::rng_i(int i)
{
    return rand() % i + 1;
}
double Chromosome::rng_ab(double a, double b)
{
    return fmod((double)rand(), a + b);
}


