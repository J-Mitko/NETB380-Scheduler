#include "schedule.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <string>

// Global variables to use in other classes
// for convenience.
int MONDAY = 0;
int TUESDAY = 1;
int WEDNESDAY = 2;
int THURSDAY = 3;
int FRIDAY = 4;
int SATURDAY= 5;

const int MAX_FITNESS = 100;

const int TIMESLOTS_PER_DAY = 6;
const int NUM_WORKING_DAYS = 6;

Schedule::Schedule(CourseDB course_db,Lecturer lectures) {
	timeslots.resize(TIMESLOTS_PER_DAY * NUM_WORKING_DAYS, 0);
	this->course_db = course_db;
    this->professors = lectures;
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
	srand(unsigned(time(0)));
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


void Schedule::fitness_calculation()
{
    int current_course_id;
    int next_course_id;

    fitness = MAX_FITNESS;

    for(int day = 0;day<6;day++)
    {
        for(int i = 0;i<timeslots.size();i++)
        {
            current_course_id = get_course_id_at(day,i);
            next_course_id = current_course_id + 1;

            //check semester <= 1
            if( course_db.get_course_with_id(current_course_id)->get_semester() <= 1)
            {
                //check if it is a theory_course or lab course
                if( course_db.get_course_with_id(current_course_id)->is_theory_course() )
                {
                    //THEORY COURSE
                    //check if theory before lab
                    if(is_theory_before_lab(day,i))
                    {
                        //check professor preference vector
                        if(professors.get_preference(day) == 0 )
                        {
                            fitness -= 15;
                        }
                        else if(professors.get_preference(day) == 1 )
                        {
                            fitness -= 10;
                        }
                        else if(professors.get_preference(day) == 2 )
                        {
                            fitness -= 7;
                        }
                        else if(professors.get_preference(day) == 3 )
                        {
                            fitness -= 5;
                        }
                        else if(professors.get_preference(day) == 4 )
                        {
                            fitness -= 3;
                        }
                        else if(professors.get_preference(day) == 5 )
                        {
                            fitness -= 1;
                        }
                    }
                    // lab before theory
                    else
                    {
                        fitness -= 25;
                        //check professor preference vector
                        if(professors.get_preference(day) == 0 )
                        {
                            fitness -= 15;
                        }
                        else if(professors.get_preference(day) == 1 )
                        {
                            fitness -= 10;
                        }
                        else if(professors.get_preference(day) == 2 )
                        {
                            fitness -= 7;
                        }
                        else if(professors.get_preference(day) == 3 )
                        {
                            fitness -= 5;
                        }
                        else if(professors.get_preference(day) == 4 )
                        {
                            fitness -= 3;
                        }
                        else if(professors.get_preference(day) == 5 )
                        {
                            fitness -= 1;
                        }
                    }
                }
            }
        }
    }
}
void Schedule::mutate()
{


}
void Schedule::keep_the_best()
{


}
