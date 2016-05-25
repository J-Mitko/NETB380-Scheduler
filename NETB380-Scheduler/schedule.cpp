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

const int TIMESLOTS_PER_DAY = 6;
const int NUM_WORKING_DAYS = 6;

Schedule::Schedule(CourseDB course_db) {
	timeslots.resize(TIMESLOTS_PER_DAY * NUM_WORKING_DAYS, 0);
	this->course_db = course_db;
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

