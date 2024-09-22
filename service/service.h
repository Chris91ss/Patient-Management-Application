#pragma once
#include <algorithm>
#include <vector>
#include <string>

#include "../repository/repository.h"
#include "../subject.h"

class Service : public Subject{
private:
    Repository *repository;
public:
    Service(Repository *repository): repository(repository) {
        repository->loadDoctorsFromFile("../data/doctors.txt");
        repository->loadPatientsFromFile("../data/patients.txt");
    }
    void addDoctorToRepo(Doctor *doctor);
    void addPatientToRepo(Patient *patient);
    vector<Doctor *> getDoctorsFromRepo();
    vector<Patient *> getPatientsFromRepo();
    void removeDoctorFromRepo(string name);
    void removePatientFromRepo(string name);
    void updatePatientFromRepo(string name, string diagnosis, string specialisation);
    Patient* searchPatientFromRepo(string name);
    Doctor* searchDoctorBySpecialisationFromRepo(string specialisation);
    vector<Patient *> getPatientsBySpecialisation(string specialisation);
};
