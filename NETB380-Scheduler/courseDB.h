#ifndef COURSEDB_H
#define COURSEDB_H

#include <map>
#include <vector>
#include "Course.h"
#include "include/libpq-fe.h"

class CourseDB {
private:
    std::map<int,Course> id_to_course_map;
public:
    CourseDB();
    CourseDB(PGresult *result);
    std::map<int,Course> get_id_to_course_map() const;
    Course* get_course_with_id(int id) ;
    int get_number_of_courses() const;
    vector<int> get_all_course_ids();
};

#endif
