#include "patient.h"

string Patient::getName() const {
    return name;
}

string Patient::getDiagnosis() const {
    return diagnosis;
}

string Patient::getSpecialisation() const {
    return specialisation;
}

string Patient::getCurrentDoctor() const {
    return currentDoctor;
}

string Patient::getAdmissionDate() const {
    return admissionDate;
}

void Patient::setName(const string &name) {
    this->name = name;
}

void Patient::setDiagnosis(const string &diagnosis) {
    this->diagnosis = diagnosis;
}

void Patient::setSpecialisation(const string &specialisation) {
    this->specialisation = specialisation;
}

void Patient::setCurrentDoctor(const string &currentDoctor) {
    this->currentDoctor = currentDoctor;
}

void Patient::setAdmissionDate(const string &admissionDate) {
    this->admissionDate = admissionDate;
}

string Patient::toString() {
    return name + ";" + diagnosis + ";" + specialisation + ";" + currentDoctor + ";" + admissionDate;
}

ostream & operator<<(ostream &os, const Patient &patient) {
    os << patient.name << ";" << patient.diagnosis << ";" << patient.specialisation << ";" << patient.currentDoctor << ";" << patient.admissionDate;
    return os;
}

istream & operator>>(istream &is, Patient &patient) {
    getline(is, patient.name, ';');
    getline(is, patient.diagnosis, ';');
    getline(is, patient.specialisation, ';');
    getline(is, patient.currentDoctor, ';');
    getline(is, patient.admissionDate);
    return is;
}




