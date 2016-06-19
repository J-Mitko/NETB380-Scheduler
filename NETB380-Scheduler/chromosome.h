#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include "schedule.h"

extern int SIZE;
extern double PXOVER ;
extern int MUTATION;

using namespace std;

class Chromosome
{
private:
    vector <Schedule> chromosomes;
    vector <Schedule> newSequence;

    static int rng_i(int i);
    static double rng_ab(double a, double b);
public:
    Chromosome();
    ~Chromosome();

    void selector();
    void mutate();
    void elitest();

    void crossover();//
    void Xover(int index, int day_1,int timeslot_1, int day_2,int timeslot_2);

    void evaluate();

};

#endif // POPULATION_H
