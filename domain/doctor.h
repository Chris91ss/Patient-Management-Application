#pragma once
#include <string>
#include <iostream>
using namespace std;

class Doctor {
private:
    string name;
    string specialisation;

public:
    Doctor() = default;
    Doctor(string name, string specialisation) : name(name), specialisation(specialisation) {}
    string getName() const;
    string getSpecialisation() const;
    void setName(const string &name);
    void setSpecialisation(const string &specialisation);
    string toString();
    friend ostream& operator<<(ostream& os, const Doctor& doctor);
    friend istream& operator>>(istream& is, Doctor& doctor);
};