#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "course.h"
using namespace std;

class Schedule {
private:
    vector<Course*> timeslot; // a 36 element vector with courses

public:
    Schedule();
};

#endif // SCHEDULE_H
