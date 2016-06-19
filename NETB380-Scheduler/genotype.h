#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include "schedule.h"

extern int MAXGENS;

using namespace std;

class Genotype
{
private:
    static int rng_i(int i);
    static double rng_ab(double a, double b);
public:
    vector <Schedule> gene;

    Genotype(Schedule init_schedule);
    ~Genotype();
};

#endif // POPULATION_H
