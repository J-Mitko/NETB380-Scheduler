#include "courseDB.h"
#include <string>
#include <iostream>

CourseDB::CourseDB(){}

CourseDB::CourseDB(PGresult* result) {
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        puts("[INFO] No data was found in table 'courses'.");
        return;
    }
    int rows = PQntuples(result);
    int cols = PQnfields(result);
    printf("[INFO] Query retrieved %d records.\n", rows);

// Not very elegant atm
    for (int row = 0; row < rows; row++) {
        int id, lecturer_id, enrolled_students, semester, degree_id, theory_course_id;
        string name;
        for (int col = 0; col < cols; col++) {
            if (col == 0) {
                id = atoi(PQgetvalue(result, row, col));
            }
            if (col == 1) {
                name = PQgetvalue(result, row, col);
            }
            if (col == 2) {
                lecturer_id = atoi(PQgetvalue(result, row, col));
            }
            if (col == 3) {
                enrolled_students = atoi(PQgetvalue(result, row, col));   
            }
            if (col == 4) {
                semester = atoi(PQgetvalue(result, row, col));
            }
            if (col == 5) {
                degree_id = atoi(PQgetvalue(result, row, col));
            }
            if (col == 6) {
                theory_course_id = atoi(PQgetvalue(result, row, col));
            }
        }
        Course course(id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id);
        id_to_course_map.insert(std::pair<int, Course>(course.get_id(), course));
    }
}

std::map<int, Course> CourseDB::get_id_to_course_map() const{
    return id_to_course_map;
}

Course* CourseDB::get_course_with_id(int id) {
    std::map<int,Course>::iterator it = id_to_course_map.find(id);
    Course* course = NULL;       
    if (it != id_to_course_map.end()) {
        course = &((*it).second);
    }
    return course;
}

int CourseDB::get_number_of_courses() const {
    return id_to_course_map.size() - 1; // - the dummy course with id:0
}

// Ignores the dummy id 0
vector<int> CourseDB::get_all_course_ids() {
    vector<int> ids;
    for (std::map<int,Course>::iterator it = id_to_course_map.begin(); it != id_to_course_map.end(); ++it) {
        if (it->first != 0)
            ids.push_back(it->first);
    }
    return ids;
}

