#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QtGui>
#include <vector>
#include "course.h"
#include "courseDB.h"
#include "lecturerDB.h"

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
    LecturerDB professors_db;

    static int rng(int i);

    int fitness;
    int relative_fitness;//relative fitness of each member.
    int cumulative_fitness;
    int day_fitness[6];

public:
    Schedule();
    Schedule(CourseDB course_db,LecturerDB lectures_db);
    int get_course_id_at(int day, int timeslot);
    void set_course_id_at(int day, int timeslot, int course_id);

    void randomize_schedule();
    void swap_timeslots(int day1, int timeslot1, int day2, int timeslot2);
    void swap_timeslots(int timeslot1, int timeslot2);

    bool is_theory_before_lab(int day, int timeslot);
    bool is_lab_before_theory(int day, int timeslot);

    void fitness_calculation();
    void professor_preference_deduction(int id,int day);
    int get_fitness();
    int get_day_fitness(int day);

    int get_relative_fitness();
    void set_relative_fitness(int var);
    int get_cumulative_fitness();
    void set_cumulative_fitness(int var);
    void print_schedule();
    void print_schedule(QStandardItemModel *model);
};

#endif // SCHEDULE_H
