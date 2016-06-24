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
#include <stdlib.h>
#include <QProgressDialog>


using namespace std;

void addSchedule (PGconn *conn, Schedule schedule) {
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("[ERR ] Could not connect to the database.");
        puts(PQerrorMessage(conn));
    }
    auto timeslots = schedule.get_timeslots();
    string timeslotsStr = "{";
    for (auto timeslot : timeslots) {
        timeslotsStr += to_string(timeslot);
        timeslotsStr += ",";
    }
    timeslotsStr[timeslotsStr.length() - 1] = '}';
    string querryString = "insert into schedules (id, timeslots) values (DEFAULT, '" + timeslotsStr + "')";
    PGresult* result = PQexec(conn, querryString.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        puts("[INFO] No data was found in table 'courses'.");
    }
    puts("Schedule stored!");
}


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    window w;
    QStringList login_input = w.login_window();

    QString conn_str = QString("dbname=%1 host=%2 user=%3 password=%4").arg(login_input[1],login_input[0],login_input[2],login_input[3]);

    string str = conn_str.toStdString();
    const char* con_char = str.c_str();
    PGconn *conn = PQconnectdb(con_char);


    if (PQstatus(conn) == CONNECTION_BAD) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Database didn't open!Probabbly wrong input.");
        messageBox.setFixedSize(500,200);
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


    w.display_settings_window();
    Chromosome newSchedule(w.get_gen(),schedule);    

    int MAXGENS = w.get_max();
    for(int i = 0;i< MAXGENS;i++)
    {
        newSchedule.crossover();
        newSchedule.mutate();
        newSchedule.evaluate();
        newSchedule.report(i);

    }


    cout << "___________________BEST SCHEDULE___________________" <<endl;
    newSchedule.print();
    addSchedule(conn, newSchedule.get_best_chromosome());

    //--------------------------GUI-----------------------------------

    for(int i=0;i<w.get_num();i++)
    {
        w.display_Table(newSchedule,i);
    }

    w.show();

    return a.exec();
    //--------------------------GUI-----------------------------------
    PQclear(result);
    PQfinish(conn);
    return 0;
}
