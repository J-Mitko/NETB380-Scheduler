#include "lecturerDB.h"

LecturerDB::LecturerDB()
{

}
LecturerDB::LecturerDB(PGresult* result)
{
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        puts("[INFO] No data was found in table 'courses'.");
        return;
    }
    int rows = PQntuples(result);
    int cols = PQnfields(result);
    printf("[INFO] Query retrieved %d records.\n", rows);

    // Not very elegant atm INDEED!
        for (int row = 0; row < rows; row++)
        {
            int id;
            string firstname;
            string lastname;

            vector<unsigned int> pref_vector;

            for (int col = 0; col < cols; col++)
            {
                if (col == 0) {
                    id = atoi(PQgetvalue(result, row, col));
                }
                if (col == 1) {
                    firstname = PQgetvalue(result, row, col);
                }
                if (col == 2) {
                    lastname = PQgetvalue(result, row, col);
                }
                if (col == 3) {
                    string pref = PQgetvalue(result, row, col);
                    if(pref.length() > 0)
                    {
                        for(unsigned int i = 0; i < pref.length();i++)
                        {
                            if(isdigit(pref[i]))
                            {
                                pref_vector.push_back(int(pref[i]-48));
                            }
                        }
                    }
                }
            }

            Lecturer professor(id,firstname,lastname,pref_vector);
            id_to_professor_map.insert(pair<int, Lecturer>(professor.get_id(),professor));
        }
}

LecturerDB::~LecturerDB()
{

}

Lecturer* LecturerDB::get_lector_with_id(int id)
{
    map<int,Lecturer>::iterator it = id_to_professor_map.find(id);
    Lecturer* profesor = NULL;
    if (it != id_to_professor_map.end()) {
        profesor = &((*it).second);
    }
    return profesor;
}
