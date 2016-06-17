#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "course.h"
#include "courseDB.h"
#include "lecturer.h"

using namespace std;

extern int MONDAY;
extern int TUESDAY;
extern int WEDNESDAY;
extern int THURSDAY;
extern int FRIDAY;
extern int SATURDAY;

extern int MAX_FITNESS;

class Schedule {
private:
    vector<int> timeslots; // a 36 element vector with course_ids
    CourseDB course_db; // _TODO_ this should really be a pointer
    Lecturer professors;

    static int rng(int i);

    int fitness;

public:
    Schedule(CourseDB course_db,Lecturer lectures);
    int get_course_id_at(int day, int timeslot);
    void set_course_id_at(int day, int timeslot, int course_id);
    void randomize_schedule();
    void swap_timeslots(int day1, int timeslot1, int day2, int timeslot2);
    void print_schedule();
    bool is_theory_before_lab(int day, int timeslot);


    void fitness_calculation();
    void mutate();
    void keep_the_best();

};

#endif // SCHEDULE_H
