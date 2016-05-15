#include "lecturer.h"

Lecturer::Lecturer()
{

}

Lecturer::Lecturer(int id,string name)
{
    _faculty_id = id;
    _name = name;
}

void Lecturer::add_course(Course *course)
{
    _courses.push_back(course);
}

void Lecturer::get_course_id(int id)
{
    //return _courses.;
}
