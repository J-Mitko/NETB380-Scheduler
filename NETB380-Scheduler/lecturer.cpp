#include "lecturer.h"

Lecturer::Lecturer()
{

}

Lecturer::Lecturer(int id,string name)
{
    this->_faculty_id = id;
    this->_name = name;
}

void Lecturer::add_course(Course *course)
{
    this->_courses.push_back(course);
}

int Lecturer::get_course_id(int id)
{
    //return this->_courses.get_;
}
