#include "lecturer.h"

Lecturer::Lecturer(){}

Lecturer::Lecturer(const int& id, const string& firstname, const string& lastname, const vector<unsigned int> &preference) {
    this->id = id;
    this->firstname = firstname;
    this->lastname = lastname;
    this->preference = preference;
}

int Lecturer::get_id() const {
    return id;
}

string Lecturer::get_firstname() const {
    return firstname;
}

string Lecturer::get_lastname() const {
    return lastname;
}

string Lecturer::get_fullname() const {
    return firstname + ' ' + lastname;
}

int Lecturer::get_preference(unsigned int day) const {
    return preference[day];
}
