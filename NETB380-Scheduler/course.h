#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "include/libpq-fe.h"
using namespace std;

class Course
{
private:
    int id;
    string name;
    int lecturer_id;
    int enrolled_students;
    int semester;
    int degree_id;
    int theory_course_id;

public:
    Course(const int& id, const string& name, const int& lecturer_id, const int& enrolled_students, const int& semester, const int& degree_id, const int& theory_course_id);

    int get_id() const;
    string get_name() const;
    int get_lecturer_id() const;
    int get_enrolled_students() const;
    int get_semester() const;
    int get_degree_id() const;
    int get_theory_course_id() const;
    bool is_theory_course() const;
};

#endif // COURSE_H
