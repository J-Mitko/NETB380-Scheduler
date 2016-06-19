#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include "schedule.h"

extern int SIZE;
extern double PXOVER ;
extern int MUTATION;

using namespace std;

class Chromosome
{
private:
    vector <Schedule> chromosomes;
    vector <Schedule> prevSequence;

    Schedule best_chromosome;

    static int rng_i(int i);
    static double rng_ab(double a, double b);
public:
    Chromosome(Schedule init_schedule);
    ~Chromosome();

    void selector(); //TODO
    void mutate();
    //void elitest();

    void crossover();//
    void Xover(int index,int timeslot_1,int timeslot_2);

    void evaluate();
    void report(int generation);
    void print();// print best_cromosome

};

#endif // POPULATION_H
