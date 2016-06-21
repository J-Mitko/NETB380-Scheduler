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
#include "mainwindow.h"
#include <QApplication>


using namespace std;

const int MAXGENS = 10;

int main(int argc, char *argv[]) {
    PGconn *conn = PQconnectdb("dbname=courseinfo host=127.0.0.1 user=postgres password=admin");

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
    //schedule.print_schedule();
    QApplication a(argc, argv);
    MainWindow w(schedule);
    //w.show();
    //return a.exec();

    //-------------TEST----------------
    Chromosome test(schedule);
    Chromosome test1(schedule);
    Chromosome test2(schedule);

//    for(int i = 0;i< MAXGENS;i++)
//    {

        //test.crossover();
        //test.mutate();
        //test.evaluate();
        cout<< "GENERATION              0                    BEGIN" <<endl;
        test.report(0);
        test2.report(0);
        cout<< "---------------------END------------------------" <<endl;

        cout<< "GENERATION              1                    BEGIN" <<endl;
        test1.report(0);
        test1.print_all(0);
        cout<< "---------------------END------------------------" <<endl;

        cout<< "GENERATION              2                    BEGIN" <<endl;
        test2.report(0);
        test2.print_all(0);
        cout<< "---------------------END------------------------" <<endl;
//    }


    cout << "________________BEST SCHEDULE________________" <<endl;
    //test.print();
    //---------------------------------

    PQclear(result);
    PQfinish(conn);
    return 0;
}
