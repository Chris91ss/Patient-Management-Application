#include "service.h"

void Service::addDoctorToRepo(Doctor *doctor) {
    repository->addDoctor(doctor);
    notify();
}

void Service::addPatientToRepo(Patient *patient) {
    if(patient->getDiagnosis() == "")
        patient->setDiagnosis("undiagnosed");
    repository->addPatient(patient);
    notify();
}

vector<Doctor *> Service::getDoctorsFromRepo() {
    return repository->getDoctors();
}

vector<Patient *> Service::getPatientsFromRepo() {
    return repository->getPatients();
}

void Service::removeDoctorFromRepo(string name) {
    repository->removeDoctor(name);
    notify();
}

void Service::removePatientFromRepo(string name) {
    repository->removePatient(name);
    notify();
}

void Service::updatePatientFromRepo(string name, string diagnosis, string specialisation) {
    repository->updatePatient(name, diagnosis, specialisation);
    notify();
}

Patient* Service::searchPatientFromRepo(string name) {
    return repository->searchPatient(name);
}

Doctor * Service::searchDoctorBySpecialisationFromRepo(string specialisation) {
    return repository->searchDoctorBySpecialisation(specialisation);
}

vector<Patient *> Service::getPatientsBySpecialisation(string specialisation) {
    vector<Patient *> patients = repository->getPatients();

    patients.erase(remove_if(patients.begin(), patients.end(), [specialisation](Patient *patient) {
        return !(patient->getSpecialisation() == specialisation || patient->getDiagnosis() == "undiagnosed");
    }), patients.end());

    sort(patients.begin(), patients.end(), [](Patient *a, Patient *b) {
        return a->getAdmissionDate() < b->getAdmissionDate();
    });

    return patients;
}

