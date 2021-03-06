#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Lecturer
{
private:
    int id;
    string firstname;
    string lastname;
    vector<unsigned int> preference; // preference level for each of the 6 daily lecutre timesots
                            // The preference order should be from 0 (lowest) to 5 (highests)

public:
    Lecturer(const int& id, const string& firstname, const string& lastname, const vector<unsigned int> &preference);

    int get_id() const;
    string get_firstname() const;
    string get_lastname() const;
    string get_fullname() const;
    int get_preference(unsigned int day) const;
};

#endif // LECTURER_H
