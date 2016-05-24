#include <cstdio>
#include <iostream>
#include <vector>
#include <QCoreApplication>

#include "include/libpq-fe.h"
#include "course.h"
#include "lecturer.h"
#include "schedule.h"
using namespace std;

void tryDbConnection() {
    PGconn *conn = PQconnectdb("dbname=courseinfo host=127.0.0.1");
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("[ERR ] Could not connect to the database.");
        puts(PQerrorMessage(conn));
        return;
    }
    puts("[INFO] Connected successfully");

    PGresult* result = PQexec(conn, "select * from courses order by id");
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        puts("[INFO] No data was found in table 'courses'.");
        return;
    }
    int rows = PQntuples(result);
    printf("[INFO] Query retrieved %d records.", rows);

    puts("");
    puts("======================================================");
    for(int row = 0; row < rows; row++) {
        for (int col = 0; col < 7; col++) {
            printf("%s\t", PQgetvalue(result, row, col));
        }
        puts("");
    }
    puts("======================================================");
    PQclear(result);
    PQfinish(conn);
}

int main()
{
    tryDbConnection();
    return 0;
}
