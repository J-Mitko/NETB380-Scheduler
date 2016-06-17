#ifndef POPULATION_H
#define POPULATION_H

#include "schedule.h"

class Population
{

private:
    vector <Schedule> population;
    vector <Schedule> newPopulation;
public:
    Population();
    ~Population();
};

#endif // POPULATION_H
