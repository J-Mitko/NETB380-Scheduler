#include <cstdio>
#include <iostream>
#include <vector>
#include <QCoreApplication>

#include "include/libpq-fe.h"
#include "course.h"
#include "lecturer.h"
#include "schedule.h"
#include "courseDB.h"
#include "lecturerDB.h"
#include "chromosome.h"


using namespace std;

int main() {
    //PGconn *conn = PQconnectdb("dbname=scheduler scheduler host=127.0.0.1 user=postgres password=admin");
    PGconn *conn = PQconnectdb("dbname=courseinfo host=127.0.0.1 user=postgres password=student1");
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("[ERR ] Could not connect to the database.");
        puts(PQerrorMessage(conn));
        return 0;
    }
    puts("[INFO] Connected successfully");

    PGresult* result = PQexec(conn, "select * from courses order by id");
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        puts("[INFO] No data was found in table 'courses'.");
        return 0;
    }
    CourseDB course_db(result);

    PQclear(result);
    result = PQexec(conn, "select * from lecturers order by id");
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        puts("[INFO] No data was found in table 'lecturers'.");
        return 0;
    }
    LecturerDB lecturer_db(result);


    Schedule schedule(course_db,lecturer_db);
    schedule.randomize_schedule();
    puts("Printing schedule...");
    schedule.swap_timeslots(MONDAY, 0, TUESDAY, 0);
    schedule.print_schedule();

    //Chromosome pop(schedule);

    PQclear(result);
    PQfinish(conn);
    return 0;
}
