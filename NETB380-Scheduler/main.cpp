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
#include "window.h"
#include <QApplication>
#include <qDebug>


using namespace std;

const int MAXGENS = 10;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    window w;
    QStringList login_input = w.login_window();
    QString conn_str = QString("dbname=%1 host=%2 user=%3 password=%4").arg(login_input[1],login_input[0],login_input[2],login_input[3]);
    string str = conn_str.toStdString();
    const char* con_char = str.c_str();
    PGconn *conn = PQconnectdb(con_char);


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


    //-------------TEST----------------
    Chromosome test(schedule);


    for(int i = 0;i< MAXGENS;i++)
    {

        test.crossover();
        test.mutate();
        test.evaluate();

        test.report(i);
        //test.print_all(i);

    }


    cout << "________________BEST SCHEDULE________________" <<endl;
    test.print();
    //---------------------------------
    //--------------------------GUI-----------------------------------
    w.display_Table(test);
    w.show();
    w.updateGeometry();
    return a.exec();
    //--------------------------GUI-----------------------------------
    PQclear(result);
    PQfinish(conn);
    return 0;
}
