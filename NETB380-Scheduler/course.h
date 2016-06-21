#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "include/libpq-fe.h"
using namespace std;

class Course
{
private:
    unsigned int id;
    string name;
    unsigned int lecturer_id;
    unsigned int enrolled_students;
    unsigned int semester;
    unsigned int degree_id;
    unsigned int theory_course_id;

public:
    Course(const unsigned int& id, const string& name, const unsigned int& lecturer_id, const unsigned int& enrolled_students, const unsigned int& semester, const unsigned int& degree_id, const unsigned int& theory_course_id);

    unsigned int get_id() const;
    string get_name() const;
    unsigned int get_lecturer_id() const;
    unsigned int get_enrolled_students() const;
    unsigned int get_semester() const;
    unsigned int get_degree_id() const;
    unsigned int get_theory_course_id() const;
    bool is_theory_course() const;
};

#endif // COURSE_H
