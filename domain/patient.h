#pragma once
#include <string>
#include <iostream>
using namespace std;

class Patient {
private:
    string name;
    string diagnosis;
    string specialisation;
    string currentDoctor;
    string admissionDate;
public:
    Patient() = default;
    Patient(string name, string diagnosis, string specialisation, string currentDoctor, string admissionDate) :
    name(name), diagnosis(diagnosis), specialisation(specialisation), currentDoctor(currentDoctor), admissionDate(admissionDate) {}

    string getName() const;
    string getDiagnosis() const;
    string getSpecialisation() const;
    string getCurrentDoctor() const;
    string getAdmissionDate() const;
    void setName(const string &name);
    void setDiagnosis(const string &diagnosis);
    void setSpecialisation(const string &specialisation);
    void setCurrentDoctor(const string &currentDoctor);
    void setAdmissionDate(const string &admissionDate);
    string toString();
    friend ostream& operator<<(ostream& os, const Patient& patient);
    friend istream& operator>>(istream& is, Patient& patient);
};