#ifndef LECTURERDB_H
#define LECTURERDB_H

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include "lecturer.h"
#include "include/libpq-fe.h"
#include <iostream>

using namespace std;

class LecturerDB
{
private:
    std::map<int,Lecturer> id_to_professor_map;
public:
    LecturerDB();
    LecturerDB(PGresult *result);

    Lecturer* get_lector_with_id(int id);

    ~LecturerDB();
};

#endif // LECTURERDB_H
