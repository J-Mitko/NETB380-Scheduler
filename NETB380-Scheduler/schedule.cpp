#include "schedule.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <window.h>
#include <qDebug>
#include <QTableWidgetItem>


// Global variables to use in other classes
// for convenience.
int MONDAY = 0;
int TUESDAY = 1;
int WEDNESDAY = 2;
int THURSDAY = 3;
int FRIDAY = 4;
int SATURDAY= 5;

const int MAX_FITNESS = 3900;

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
}

unsigned int Schedule::get_course_id_at(unsigned int day, unsigned int timeslot) {
	int index = TIMESLOTS_PER_DAY * day + timeslot;
	return timeslots[index];
}

void Schedule::set_course_id_at(unsigned int day, unsigned int timeslot, unsigned int course_id) {
	int index = TIMESLOTS_PER_DAY * day + timeslot;
	timeslots[index] = course_id;
}

vector<unsigned int> Schedule::get_timeslots() const {
    return timeslots;
}

int Schedule::rng(unsigned int i) {
	return rand() % i;
}

void Schedule::randomize_schedule() {
    vector<unsigned int> ids = course_db.get_all_course_ids();
	ids.resize(36, 0);
	timeslots = ids;
    random_shuffle(timeslots.begin(), timeslots.end(),rng); // randomize
}

void Schedule::swap_timeslots(unsigned int day1, unsigned int timeslot1, unsigned int day2, unsigned int timeslot2) {
	int index1 = TIMESLOTS_PER_DAY * day1 + timeslot1;
	int index2 = TIMESLOTS_PER_DAY * day2 + timeslot2;
	int temp_course_id = timeslots[index1];
	timeslots[index1] = timeslots[index2];
	timeslots[index2] = temp_course_id;
}

void Schedule::swap_timeslots(unsigned int timeslot1, unsigned int timeslot2)
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

void Schedule::print_schedule(QTableWidget* model) {
    for (int i = 0; i < NUM_WORKING_DAYS * TIMESLOTS_PER_DAY; i++) {
        int course_id = timeslots[i];
        if (course_id == 0) { // i.e. dummy course id
            QTableWidgetItem * index = new QTableWidgetItem ("FREE");
            model->setItem(i%6,i/6,index);
            continue;
        }
        Course* course = course_db.get_course_with_id(course_id);
        if (course == NULL) {
            QTableWidgetItem *  index = new QTableWidgetItem ("FREE");
            model->setItem(i%6,i/6,index);
            continue;
        }
        QTableWidgetItem *  index = new QTableWidgetItem (QString::fromStdString(course->get_name()));
        model->setItem(i%6,i/6,index);
    }
}

// Give a timeslot and if it has s lab course in it
// it will return wether it is after the theory
bool Schedule::is_theory_before_lab(unsigned int day, unsigned int timeslot) {
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
bool Schedule::is_lab_before_theory(unsigned int day, unsigned int timeslot)
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
    int current_course_id =0;
    fitness = MAX_FITNESS;// RESET FITNESS VALUE

    for(int day = 0;day<6;day++)
    {
        for(int slot = 0;slot<6;slot++)//6 timeslots a day
        {
            current_course_id = this->get_course_id_at(day,slot);
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
                        if(is_theory_before_lab(day,slot))
                        {
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                        // lab before theory
                        else
                        {
                            fitness -= 120;
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                    }
                    else // LAB Course
                    {
                        if(is_lab_before_theory(day,slot))// lab before theory
                        {
                            fitness -= 120;
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

                    //check if it is a theory_course or lab course
                    if( course_db.get_course_with_id(current_course_id)->is_theory_course() )
                    {
                        //THEORY COURSE
                        //check if theory before lab
                        if(is_theory_before_lab(day,slot))
                        {
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                        // lab before theory
                        else
                        {
                            fitness -= 120;
                            professor_preference_deduction(course_db.get_course_with_id(current_course_id)->get_lecturer_id(),day);//check professor preference vector
                        }
                    }
                    else // LAB Course
                    {
                        if(is_lab_before_theory(day,slot))// lab before theory
                        {
                            fitness -= 120;
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

void Schedule::professor_preference_deduction(unsigned int id, unsigned int day)
{
    //-25*6 = 150
    if(professors_db.get_lector_with_id(id)->get_preference(day) == 0 )
    {
        fitness -= 10;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 1 )
    {
        fitness -= 5;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 2 )
    {
        fitness -= 4;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 3 )
    {
        fitness -= 3;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 4 )
    {
        fitness -= 2;
    }
    else if(professors_db.get_lector_with_id(id)->get_preference(day) == 5 )
    {
        fitness -= 1;
    }
}

int Schedule::get_fitness()
{
    return fitness;
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
