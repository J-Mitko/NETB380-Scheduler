#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <ctime>
#include <stdlib.h>
#include "schedule.h"

extern int POPULATION_SIZE;
extern int MAXGENS;
extern int NVARS; //6 for six days
extern int MUTATION;// chance for mutation

using namespace std;

class Population
{

private:
    vector <Schedule> population;
    vector <Schedule> newPopulation;

    static int rng_i(int i);
    static int rng_ab(int a, int b);
public:
    Population(Schedule init_schedule);
    ~Population();

    void elitist();

    void mutate();

};

#endif // POPULATION_H
