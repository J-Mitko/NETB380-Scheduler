#include "course.h"

Course::Course()
{

}
Course::Course(int id,string name,int number_students,int max_students, Lecturer* lecturer)
{

    _id = id;
    _name = name;
    _number_students = number_students;
    _max_number_students = max_students;

    _lecturer = lecturer;
}

int Course::get_course_id()
{
    return _id;
}
int Course::get_number_students()
{
    return _number_students;
}
int Course::get_max_number_students()
{
    return _max_number_students;
}

int Course::get_lecturer(Lecturer &lecturer)
{
    return 0;
}

