#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>


gui::gui(QWidget *parent, Service *service, Doctor *doctor) : QWidget(parent), ui(new Ui::gui), service(service), doctor(doctor){
    ui->setupUi(this);

    service->registerObserver(this);

    this->setWindowTitle(QString::fromStdString(doctor->getName()));

    this->updateList();

    QObject::connect(this->ui->checkBox, &QCheckBox::stateChanged, this, &gui::updateMyPatients);
    QObject::connect(this->ui->addButton, &QPushButton::clicked, this, &gui::addPatient);
    QObject::connect(this->ui->updateButton, &QPushButton::clicked, this, &gui::updatePatients);
}

gui::~gui() {
    delete ui;
}

void gui::updateList() {
    this->ui->patientsListWidget->clear();
    for(Patient *patient: service->getPatientsBySpecialisation(doctor->getSpecialisation())) {
        auto item = new QListWidgetItem(QString::fromStdString(patient->toString()));
        if(patient->getCurrentDoctor() == doctor->getName()) {
            item->setBackground(Qt::green);
        }
        this->ui->patientsListWidget->addItem(item);
    }
}

void gui::updateMyPatients() {
    this->ui->patientsListWidget->clear();

    if(this->ui->checkBox->isChecked()) {
        for(Patient *patient: service->getPatientsBySpecialisation(doctor->getSpecialisation())) {
            if(patient->getCurrentDoctor() == doctor->getName()) {
                auto item = new QListWidgetItem(QString::fromStdString(patient->toString()));
                item->setBackground(Qt::green);
                this->ui->patientsListWidget->addItem(item);
            }
        }
    } else {
        this->updateList();
    }
}

void gui::addPatient() {
    string name = this->ui->nameLineEdit->text().toStdString();
    string diagnosis = this->ui->diagnosisLineEdit->text().toStdString();
    string specialisation = this->ui->specialisationLineEdit->text().toStdString();
    string doctor = this->ui->currentDoctorLineEdit->text().toStdString();
    string date = this->ui->admissionDateLineEdit->text().toStdString();

    if(name.empty() || date.empty()) {
        QMessageBox::critical(this, "Error", "Name and date cannot be empty");
        return;
    }

    if(date < "2024-06-21") {
        QMessageBox::critical(this, "Error", "Date cannot be in the past");
        return;
    }

    Patient *patient = new Patient(name, diagnosis, specialisation, doctor, date);

    service->addPatientToRepo(patient);
    this->updateList();
}

void gui::updatePatients() {
    string name = this->ui->updateNameLineEdit->text().toStdString();
    string diagnosis = this->ui->updateDiagnosisLineEdit->text().toStdString();
    string specialisation = this->ui->updateSpecialisationLineEdit->text().toStdString();

    if (diagnosis == "undiagnosed") {
        QMessageBox::critical(this, "Error", "Diagnosis cannot be 'undiagnosed'");
        return;
    }

    Patient *patientToUpdate = service->searchPatientFromRepo(name);

    if (!patientToUpdate) {
        QMessageBox::critical(this, "Error", "Patient not found");
        return;
    }

    string currentDoctor = patientToUpdate->getCurrentDoctor();

    if (patientToUpdate->getDiagnosis() != "undiagnosed" && currentDoctor != doctor->getName()) {
        QMessageBox::critical(this, "Error", "You can only update patients without a diagnosis or your own patients");
        return;
    }

    patientToUpdate->setDiagnosis(diagnosis);
    patientToUpdate->setSpecialisation(specialisation);


    if(doctor->getSpecialisation() != specialisation) {
        patientToUpdate->setCurrentDoctor("");
        Doctor *newDoctor = service->searchDoctorBySpecialisationFromRepo(specialisation);
        if(newDoctor) {
            patientToUpdate->setCurrentDoctor(newDoctor->getName());
        }
    } else {
        patientToUpdate->setCurrentDoctor(doctor->getName());
    }

    service->updatePatientFromRepo(name, diagnosis, specialisation);
}

void gui::update() {
    updateList();
}
