#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include "schedule.h"

extern int POPULATION_SIZE;
extern int MAXGENS;
extern int NVARS; //6 for six days
extern int MUTATION;// chance for mutation

using namespace std;

class Genotype
{

private:
    vector <Schedule> gene;

    static int rng_i(int i);
    static double rng_ab(double a, double b);
public:
    Genotype(Schedule init_schedule);
    ~Genotype();

    void elitist();
    void selector();
    void mutate();

};

#endif // POPULATION_H
