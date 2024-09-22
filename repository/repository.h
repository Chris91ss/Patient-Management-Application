#pragma once
#include <vector>
#include <string>
#include "../domain/doctor.h"
#include "../domain/patient.h"
using namespace std;
#include <sstream>
#include <fstream>


class Repository {
private:
    vector<Doctor*> doctors;
    vector<Patient*> patients;
public:
    Repository() = default;
    ~Repository() = default;
    void addDoctor(Doctor* doctor);
    void addPatient(Patient* patient);
    vector<Doctor*> getDoctors();
    vector<Patient*> getPatients();
    void removeDoctor(string name);
    void removePatient(string name);
    void updatePatient(string name, string diagnosis, string specialisation);
    Patient* searchPatient(string name);
    Doctor* searchDoctorBySpecialisation(string specialisation);
    void saveDoctorsToFile(const string &filename);
    void savePatientsToFile(const string &filename);
    void loadDoctorsFromFile(const string& filename);
    void loadPatientsFromFile(const string& filename);
};