#include "lecturer.h"

Lecturer::Lecturer()
{

}

Lecturer::Lecturer(int id,string name)
{
    this->_faculty_id = id;
    this->_name = name;
}

void Lecturer::add_course(Course &course)
{
    this->_courses.push_back(&course);
}

int Lecturer::get_course_id(int id)
{
    for(int i = 0;i <= _courses.size();i++)
    {
        if(_courses.at(i)->get_course_id() == id)
            return _courses.at(i)->get_course_id();
    }
    return -1;// if no match is found - (-1)
}

void Lecturer::set_pref_matrix(int arr[][6])
{
    for(int i = 0;i<6;i++)
    {
        for(int j = 0;j< 6;j++)
        {
            this->_prefrence_matrix[i][j] = arr[i][j];
        }
    }
}

int Lecturer::get_pref_matrix(int index_1, int index_2)
{
    return _prefrence_matrix[index_1][index_2];
}
