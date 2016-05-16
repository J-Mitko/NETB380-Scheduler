#include "studentgroup.h"

StudentGroup::StudentGroup()
{

}

StudentGroup::StudentGroup(int id, const string& name, int numberOfStudents)
{
    this->_id = id;
    this->_name = name;
    this->_number_students = numberOfStudents;
}

void StudentGroup::add_course(Course *course)
{
    _courses.push_back(course);
}
