#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include <vector>
#include <course.h>

using namespace std;

class Course;

class Lecturer
{
private:
    int _faculty_id;
    string _name;

    int _prefrence_matrix[6][6];

    // List of classes that professor teaches
    vector<Course*> _courses;
public:
    Lecturer();
    Lecturer(int id,string name);

    void add_course(Course& course);
    int get_course_id(int id);

    void set_pref_matrix(int arr[][6]);
    int get_pref_matrix(int index_1,int index_2);

    void sort();
    bool sort_by();
};

#endif // LECTURER_H
