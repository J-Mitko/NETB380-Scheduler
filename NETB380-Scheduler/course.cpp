#include "course.h"
#include <cstdio> // should use exceptions later
#include <stdlib.h>

Course::Course(const unsigned int &id, const string& name, const unsigned int &lecturer_id, const unsigned int &enrolled_students, const unsigned int &semester, const unsigned int &degree_id, const unsigned int &theory_course_id)
{
    this->id = id;
    this->name = name;
    this->lecturer_id = lecturer_id;
    this->enrolled_students = enrolled_students;
    this->semester = semester;
    this->degree_id = degree_id;
    this->theory_course_id = theory_course_id;
}

unsigned int Course::get_id() const
{
    return id;
}

string Course::get_name() const {
    return name;
}

unsigned int Course::get_lecturer_id() const {
    return lecturer_id;
}

unsigned int Course::get_enrolled_students() const {
    return enrolled_students;
}

unsigned int Course::get_semester() const {
    return semester;
}

unsigned int Course::get_degree_id() const {
    return degree_id;
}

unsigned int Course::get_theory_course_id() const {
    return theory_course_id;
}

bool Course::is_theory_course() const {
    return theory_course_id == 0;
}

