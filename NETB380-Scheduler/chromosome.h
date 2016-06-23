#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <random>

#include "schedule.h"

extern int GENEPOOL;
extern double PXOVER ;
extern int MUTATION;

using namespace std;

class Chromosome
{
    vector <Schedule> chromosomes;
    vector <Schedule> prevSequence;

    Schedule best_chromosome;

    static int rng_i(int i);
    static double rng_ab();
public:
    Chromosome(int genepool, Schedule init_schedule);
    ~Chromosome();

    void selector(); //TODO
    void mutate();

    void crossover();//
    void Xover(int index,int timeslot_1,int timeslot_2);

    void evaluate();
    void report(int generation);
    void print();// print best_cromosome

    void print_all(int i);
    Schedule get_best_chromosome();
};

#endif // POPULATION_H
