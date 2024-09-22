#include "doctor.h"

string Doctor::getName() const {
    return name;
}

string Doctor::getSpecialisation() const {
    return specialisation;
}

void Doctor::setName(const string &name) {
    this->name = name;
}

void Doctor::setSpecialisation(const string &specialisation) {
    this->specialisation = specialisation;
}

string Doctor::toString() {
    return name + ";" + specialisation;
}

ostream & operator<<(ostream &os, const Doctor &doctor) {
    os << doctor.name << ";" << doctor.specialisation;
    return os;
}

istream & operator>>(istream &is, Doctor &doctor) {
    getline(is, doctor.name, ';');
    getline(is, doctor.specialisation);
    return is;
}
