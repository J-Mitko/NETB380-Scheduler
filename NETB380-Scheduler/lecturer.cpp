#include "lecturer.h"

Lecturer::Lecturer(const int& id, const string& firstname, const string& lastname, const vector<int>& preference) {
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

vector<int> Lecturer::get_preference() const {
    return preference;
}
