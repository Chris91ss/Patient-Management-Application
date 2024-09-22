#include "repository.h"

void Repository::addDoctor(Doctor *doctor) {
    this->doctors.push_back(doctor);
}

void Repository::addPatient(Patient *patient) {
    this->patients.push_back(patient);
    this->savePatientsToFile("../data/patients.txt");
}

vector<Doctor *> Repository::getDoctors() {
    return this->doctors;
}

vector<Patient *> Repository::getPatients() {
    return this->patients;
}

void Repository::removeDoctor(string name) {
    for (int i = 0; i < doctors.size(); i++) {
        if (doctors[i]->getName() == name) {
            doctors.erase(doctors.begin() + i);
            return;
        }
    }
}

void Repository::removePatient(string name) {
    for (int i = 0; i < patients.size(); i++) {
        if (patients[i]->getName() == name) {
            patients.erase(patients.begin() + i);
            this->savePatientsToFile("../data/patients.txt");
            return;
        }
    }
}

void Repository::updatePatient(string name, string diagnosis, string specialisation) {
    for (int i = 0; i < patients.size(); i++) {
        if (patients[i]->getName() == name) {
            patients[i]->setDiagnosis(diagnosis);
            patients[i]->setSpecialisation(specialisation);
            this->savePatientsToFile("../data/patients.txt");
            return;
        }
    }
}

Patient *Repository::searchPatient(string name) {
    for (const auto& patient : patients) {
        if (patient->getName() == name) {
            return patient;
        }
    }
    return nullptr;
}

Doctor * Repository::searchDoctorBySpecialisation(string specialisation) {
    for (const auto& doctor : doctors) {
        if (doctor->getSpecialisation() == specialisation) {
            return doctor;
        }
    }
    return nullptr;
}

void Repository::saveDoctorsToFile(const string &filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& doctor : doctors) {
            outFile << *doctor << endl;
        }
        outFile.close();
    }
}

void Repository::savePatientsToFile(const string &filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& patient : patients) {
            outFile << *patient << endl;
        }
        outFile.close();
    }
}

void Repository::loadDoctorsFromFile(const string &filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            istringstream stream(line);
            Doctor *doctor = new Doctor();
            stream >> *doctor;
            this->doctors.push_back(doctor);
        }
        inFile.close();
    }
}

void Repository::loadPatientsFromFile(const string &filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            istringstream stream(line);
            Patient *patient = new Patient();
            stream >> *patient;
            this->patients.push_back(patient);
        }
        inFile.close();
    }
}


