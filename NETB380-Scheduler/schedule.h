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
    vector<unsigned int> timeslots; // a 36 element vector with course_ids
    CourseDB course_db; // _TODO_ this should really be a pointer
    LecturerDB professors_db;

    int rng(unsigned int i);

    int fitness;
    int relative_fitness;//relative fitness of each member.
    int cumulative_fitness;

public:
    Schedule();
    Schedule(CourseDB course_db,LecturerDB lectures_db);
    int get_course_id_at(unsigned int day, unsigned int timeslot);
    void set_course_id_at(unsigned int day, unsigned int timeslot, unsigned int course_id);

    void randomize_schedule();
    void swap_timeslots(unsigned int day1, unsigned int timeslot1, unsigned int day2, unsigned int timeslot2);
    void swap_timeslots(unsigned int timeslot1, unsigned int timeslot2);

    bool is_theory_before_lab(unsigned int day, unsigned int timeslot);
    bool is_lab_before_theory(unsigned int day, unsigned int timeslot);

    void fitness_calculation();
    void professor_preference_deduction(unsigned int id,unsigned int day);
    int get_fitness();

    int get_relative_fitness();
    void set_relative_fitness(int var);
    int get_cumulative_fitness();
    void set_cumulative_fitness(int var);
    void print_schedule();
    void print_schedule(QStandardItemModel *model);
};

#endif // SCHEDULE_H
