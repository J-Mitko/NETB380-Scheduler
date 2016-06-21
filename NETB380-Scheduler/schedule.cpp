#include "schedule.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <mainwindow.h>
#include <qDebug>

// Global variables to use in other classes
// for convenience.
int MONDAY = 0;
int TUESDAY = 1;
int WEDNESDAY = 2;
int THURSDAY = 3;
int FRIDAY = 4;
int SATURDAY= 5;

const int MAX_FITNESS = 3900;
const int MAX_DAY_FITNESS = 660;

const int TIMESLOTS_PER_DAY = 6;
const int NUM_WORKING_DAYS = 6;

Schedule::Schedule()
{}

Schedule::Schedule(CourseDB course_db,LecturerDB lectures_db) {
    srand(unsigned(time(0)));

    timeslots.resize(TIMESLOTS_PER_DAY * NUM_WORKING_DAYS, 0);
	this->course_db = course_db;
    this->professors_db = lectures_db;


    fitness = MAX_FITNESS;
    relative_fitness = 0;
    cumulative_fitness = 0;
    for(int i = 0;i<6;i++)
    {
        day_fitness[i] = MAX_DAY_FITNESS;
    }
}

int Schedule::get_course_id_at(int day, int timeslot) {
	int index = TIMESLOTS_PER_DAY * day + timeslot;
	return timeslots[index];
}

void Schedule::set_course_id_at(int day, int timeslot, int course_id) {
	int index = TIMESLOTS_PER_DAY * day + timeslot;
	timeslots[index] = course_id;
}

int Schedule::rng(int i) {
	return rand() % i;
}

void Schedule::randomize_schedule() {
	vector<int> ids = course_db.get_all_course_ids();
	ids.resize(36, 0);
	timeslots = ids;
	random_shuffle(timeslots.begin(), timeslots.end(), rng); // randomize
}

void Schedule::swap_timeslots(int day1, int timeslot1, int day2, int timeslot2) {
	int index1 = TIMESLOTS_PER_DAY * day1 + timeslot1;
	int index2 = TIMESLOTS_PER_DAY * day2 + timeslot2;
	int temp_course_id = timeslots[index1];
	timeslots[index1] = timeslots[index2];
	timeslots[index2] = temp_course_id;
}

void Schedule::swap_timeslots(int timeslot1, int timeslot2)
{
    int temp_course_id = timeslots[timeslot1];
    timeslots[timeslot1] = timeslots[timeslot2];
    timeslots[timeslot2] = temp_course_id;
}

void Schedule::print_schedule() {
	for (int i = 0; i < NUM_WORKING_DAYS * TIMESLOTS_PER_DAY; i++) {
		if (i % TIMESLOTS_PER_DAY == 0) {
			puts("");
		}
		int course_id = timeslots[i];
		if (course_id == 0) { // i.e. dummy course id
			puts("FREE");
			continue;
		}
		Course* course = course_db.get_course_with_id(course_id);
		if (course == NULL) {
			puts("FREE");
			continue;
		}
		string course_name = course->get_name();
		puts(course_name.c_str());
	}
}
void Schedule::print_schedule(QStandardItemModel* model) {
    for (int i = 0; i < NUM_WORKING_DAYS * TIMESLOTS_PER_DAY; i++) {
        int course_id = timeslots[i];
        if (course_id == 0) { // i.e. dummy course id
            QModelIndex index = model->index(i%6,i/6,QModelIndex());
            model->setData(index,"FREE");
            continue;
        }
        Course* course = course_db.get_course_with_id(course_id);
        if (course == NULL) {
            QModelIndex index = model->index(i%6,i/6,QModelIndex());
            model->setData(index,"FREE");
            continue;
        }
        string course_name = course->get_name();
        QModelIndex index = model->index(i%6,i/6,QModelIndex());
        model->setData(index,course_name.c_str());
    }
}

// Give a timeslot and if it has s lab course in it
// it will return wether it is after the theory
bool Schedule::is_theory_before_lab(int day, int timeslot) {
	int index = TIMESLOTS_PER_DAY * day + timeslot;

    if (timeslots[index] == 0)//first course of the day
		return true;

    Course* course = course_db.get_course_with_id(timeslots[index]);
	int theory_course_id = course->get_theory_course_id();

    if (theory_course_id == 0)
		return true;

	for (int i = index + 1; i < TIMESLOTS_PER_DAY * NUM_WORKING_DAYS; i++) {
		if (timeslots[i] == theory_course_id)
			return false;
	}
	return true;
}


// it will return weather or not it is before the theory
// FUTURE HEADAKES
bool Schedule::is_lab_before_theory(int day, int timeslot)
{
    int index = TIMESLOTS_PER_DAY * day + timeslot;

    if (timeslots[index] == 0)//first course of the day
        return false;

    Course* course = course_db.get_course_with_id(timeslots[index]);
    int theory_course_id = course->get_theory_course_id();

    if (theory_course_id == 0)
        return false;

    for (int i = index + 1; i < TIMESLOTS_PER_DAY * NUM_WORKING_DAYS; i++) {
        if (timeslots[i] == theory_course_id)
            return true;
    }
    return false;
}

void Schedule::fitness_calculation()
{
    int current_course_id;

    for(int day = 0;day<6;day++)
    {
        for(int i = 0;i<6;i++)//6 timeslots a day
        //for(int i = 0;i<timeslots.size();i++)
        {
            current_course_id = get_course_id_at(day,i);
            if(current_course_id != 0) // not dummy course
            {
                //check semester <= 1
                //-120
                if( course_db.get_course_with_id(current_course_id)->get_semester() <= 1)
                {
                    //check if it is a theory_course or lab course
                    if( course_db.get_course_with_id(current_course_id)->is_theory_course() )
                    {
                        //THEORY COURSE
                        //check if theory before lab
                        if(is_theory_before_lab(day,i))
                        {
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                        // lab before theory
                        else
                        {
                            fitness -= 120;
                            day_fitness[day] -=120;
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                    }
                    else // LAB Course
                    {
                        if(is_lab_before_theory(day,i))// lab before theory
                        {
                            fitness -= 120;
                            day_fitness[day] -=120;
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }

                        else
                        {
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                    }
                }
                else
                {//-420
                    fitness -= 300;
                    day_fitness[day] -=300;

                    //check if it is a theory_course or lab course
                    if( course_db.get_course_with_id(current_course_id)->is_theory_course() )
                    {
                        //THEORY COURSE
                        //check if theory before lab
                        if(is_theory_before_lab(day,i))
                        {
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                        // lab before theory
                        else
                        {
                            fitness -= 120;
                            day_fitness[day] -=120;
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                    }
                    else // LAB Course
                    {
                        if(is_lab_before_theory(day,i))// lab before theory
                        {
                            fitness -= 120;
                            day_fitness[day] -=120;
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                        else
                        {
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                    }

                }
            }
        }
    }
}

void Schedule::professor_preference_deduction(int id, int day)
{
    //-25*6 = 150
    if(professors_db.get_lector_with_id(id)->get_preference(day) == 0 )
    {
        fitness -= 10;
        day_fitness[day] -=10;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 1 )
    {
        fitness -= 5;
        day_fitness[day] -=5;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 2 )
    {
        fitness -= 4;
        day_fitness[day] -=4;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 3 )
    {
        fitness -= 3;
        day_fitness[day] -=3;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 4 )
    {
        fitness -= 2;
        day_fitness[day] -=2;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 5 )
    {
        fitness -= 1;
        day_fitness[day] -=1;
    }
}

int Schedule::get_fitness()
{
    return fitness;
}
int Schedule::get_day_fitness(int day)
{
    return day_fitness[day];
}

int Schedule::get_relative_fitness()
{
    return relative_fitness;
}
void Schedule::set_relative_fitness(int var)
{
    relative_fitness = var;
}
int Schedule::get_cumulative_fitness()
{
    return cumulative_fitness;
}
void Schedule::set_cumulative_fitness(int var)
{
    cumulative_fitness = var;
}
