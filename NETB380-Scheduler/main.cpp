#include <cstdio>
#include <iostream>
#include <vector>
#include <QCoreApplication>

#include "include/libpq-fe.h"
#include "course.h"
#include "lecturer.h"
#include "schedule.h"
#include "courseDB.h"
using namespace std;

int main() {
    PGconn *conn = PQconnectdb("dbname=courseinfo host=127.0.0.1 user=postgres pass=student1");
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
/*
    Schedule schedule(course_db);
    schedule.randomize_schedule();
    puts("Printing schedule...");
    schedule.swap_timeslots(MONDAY, 0, TUESDAY, 0);
    schedule.print_schedule();
*/
    PQclear(result);
    PQfinish(conn);
    return 0;
}
