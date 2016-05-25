#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "course.h"
#include "courseDB.h"
using namespace std;

extern int MONDAY;
extern int TUESDAY;
extern int WEDNESDAY;
extern int THURSDAY;
extern int FRIDAY;
extern int SATURDAY;

class Schedule {
private:
    vector<int> timeslots; // a 36 element vector with course_ids
    CourseDB course_db; // _TODO_ this should really be a pointer

    static int rng(int i);

public:
    Schedule(CourseDB course_db);
    int get_course_id_at(int day, int timeslot);
    void set_course_id_at(int day, int timeslot, int course_id);
    void randomize_schedule();
    void print_schedule();
};

#endif // SCHEDULE_H
