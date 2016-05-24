#include "course.h"

Course::Course(const int& id, const string& name, const int& lecturer_id, const int& enrolled_students, const int& semester, const int& degree_id, const int& theory_course_id)
{
    this->id = id;
    this->name = name;
    this->lecturer_id = lecturer_id;
    this->enrolled_students = enrolled_students;
    this->semester = semester;
    this->degree_id = degree_id;
    this->theory_course_id = theory_course_id;
}

int Course::get_id() const
{
    return id;
}

string Course::get_name() const {
    return name;
}

int Course::get_lecturer_id() const {
    return lecturer_id;
}

int Course::get_enrolled_students() const {
    return enrolled_students;
}

int Course::get_semester() const {
    return semester;
}

int Course::get_degree_id() const {
    return degree_id;
}

int Course::get_theory_course_id() const {
    return theory_course_id;
}

bool Course::is_theory_course() const {
    return theory_course_id == 0;
}

