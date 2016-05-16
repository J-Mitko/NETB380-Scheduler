#ifndef STUDENTGROUP_H
#define STUDENTGROUP_H

#include <course.h>

#include <lecturer.h>

#include <list>
#include <string>

using namespace std;

class Course;

class StudentGroup
{
private:
    int _id;
    string _name;

    int _number_students;

    // List of classes that group attends
    list<Course*> _courses;

public:
    StudentGroup();
    StudentGroup(int _id, const string& _name, int _numberOfStudents);

    void add_course(Course* course);

    int get_group_id();
    int get_number_students();

    // Returns reference to list of classes that group attends
    list<Course*>& get_courses();
};

#endif // STUDENTGROUP_H
