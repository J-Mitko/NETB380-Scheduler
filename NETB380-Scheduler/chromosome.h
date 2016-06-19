#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include "schedule.h"

extern int MAXGENS;

using namespace std;

class Chromosome
{
private:
    static int rng_i(int i);
    static double rng_ab(double a, double b);
public:
    vector <Schedule> gene;

    Chromosome(Schedule init_schedule);
    ~Chromosome();
};

#endif // POPULATION_H
