#ifndef COURSE_H
#define COURSE_H

#include <lecturer.h>
#include <studentgroup.h>
#include <string>

using namespace std;

class Lecturer;
class StudentGroup;

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
    StudentGroup* _group;

public:
    Course();

    Course(int id, string name, int number_students, int max_students, Lecturer *lecturer, StudentGroup *studentgroup);

    int get_course_id();
    int get_number_students();
    int get_max_number_students();

    int get_lecturer(Lecturer& lecturer);
    int get_student_group(StudentGroup& group);

};

#endif // COURSE_H
