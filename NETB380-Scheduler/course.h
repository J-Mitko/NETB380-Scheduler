#ifndef COURSE_H
#define COURSE_H

#include <lecturer.h>
#include <string>

using namespace std;

class Lecturer;

class Course
{
private:
    int _id;
    string _name;

    int _semester;
    bool _lab;

    int _number_students;
    int _max_number_students;

    Lecturer* _lecturer;

public:
    Course();

    Course(int id, string name, int number_students, int max_students, Lecturer *lecturer);

    int get_course_id();
    int get_number_students();
    int get_max_number_students();

    int get_lecturer(Lecturer& lecturer);

};

#endif // COURSE_H
