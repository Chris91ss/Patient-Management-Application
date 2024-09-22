# Patient Management Application

## Overview
The **Patient Management System** is a C++ application designed to manage doctor-patient relationships in a hospital setting. It allows doctors to view and update information about their patients, including managing diagnoses and specializations. The application provides a **Qt-based GUI** for interacting with the data, and it follows a layered architecture with separation between **data**, **service**, and **UI** layers.

The application uses the **Observer design pattern** to notify all doctors when changes occur. The doctor and patient information is loaded from text files and saved back to the files upon any modifications.

## Key Features:
1. **Doctor Management**: Doctors' information is loaded from a text file containing each doctor’s name and specialization.
2. **Patient Management**: Patients have associated information such as name, diagnosis, current doctor, specialization, and admission date.
3. **Patient Filtering**: Doctors can filter and view only the patients they are currently managing or see all patients.
4. **Patient Updates**: Doctors can update patient diagnoses and specializations. If a patient's diagnosis or specialization changes, they are reassigned to the appropriate doctor.
5. **Add New Patients**: Doctors can add new patients to the system, inputting all required information (name, diagnosis, admission date, etc.).
6. **Observer Pattern**: When one doctor makes a modification, all other doctors are notified of the changes in real-time.
7. **Persistent Data**: The system saves patient and doctor data to text files when the application closes.

## Installation:

### Prerequisites:
- **C++17** or later
- **Qt5** or later (for GUI)

Install Qt by following the [Qt Documentation](https://doc.qt.io/qt-5/gettingstarted.html).

### Clone the Repository:
```bash
git clone https://github.com/Chris91ss/Patient-Management-System.git
cd Patient-Management-System
```

### Build the Application

1. Open the project in **Qt Creator** or configure it using **CMake** for manual building.
2. Compile and run the project through your preferred method.

---

### Running the Application:

1. **Compile** the project using your preferred IDE (e.g., **Qt Creator**) or from the command line with `g++`:

```bash
g++ -o PatientManagementApp main.cpp $(pkg-config --cflags --libs Qt5Widgets)
```

2. **Run** the compiled executable:

```bash
./PatientManagementApp
```

Upon launching, the application will create a window for each doctor, displaying the patients they are responsible for.

---

## Project Structure

```plaintext
├── data                       # Stores text files for doctor and patient data
│   ├── doctors.txt             # Doctor information (name, specialization)
│   └── patients.txt            # Patient data (name, diagnosis, specialization, admission date, etc.)
├── domain                     # Domain models for Doctors and Patients
│   ├── doctor.cpp              # Implementation of Doctor class
│   ├── doctor.h                # Header file for Doctor class
│   ├── patient.cpp             # Implementation of Patient class
│   ├── patient.h               # Header file for Patient class
├── repository                 # Handles data storage/retrieval from files
│   ├── repository.cpp          # Implementation of Repository class
│   ├── repository.h            # Header file for Repository class
├── service                    # Business logic layer and UI components
│   ├── gui.cpp                 # Implementation of GUI logic
│   ├── gui.h                   # Header file for GUI class
│   ├── gui.ui                  # Qt Designer form for GUI
│   ├── main.cpp                # Entry point for the application
├── observer                   # Observer pattern implementation for real-time updates
│   ├── observer.h              # Header file for Observer design pattern
│   ├── subject.h               # Subject class to notify Observers
└── README.md                  # Documentation file
```

---

## Code Overview

### 1. **Domain Layer (`domain/`)**:
The domain layer contains the models for **Doctor** and **Patient**, defining their attributes and behavior.

### 2. **Repository Layer (`repository/`)**:
The repository layer handles data persistence. The **Repository** class provides methods to add, remove, and update doctors and patients, and it reads/writes to the respective text files.

### 3. **Service Layer (`service/`)**:
The service layer provides the main application logic, including adding and updating patients and interacting with the repository. It implements the **Observer pattern** for real-time updates.

#### `service.h`
```cpp
#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include "../repository/repository.h"
#include "../subject.h"

class Service : public Subject {
private:
    Repository *repository;
public:
    Service(Repository *repository);
    void addDoctorToRepo(Doctor *doctor);
    void addPatientToRepo(Patient *patient);
    // Other methods omitted for brevity...
};
```

#### `service.cpp`
```cpp
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
```

### 4. **Observer Pattern (`observer/`)**:
The observer pattern ensures that all doctors see real-time updates when a patient's information is modified.

#### `observer.h`
```cpp
#pragma once

class Observer {
public:
    virtual void update() = 0;
};
```

#### `subject.h`
```cpp
#pragma once
#include <algorithm>
#include <vector>
#include "observer.h"

using namespace std;

class Subject {
private:
    vector<Observer*> observers;
public:
    void registerObserver(Observer* observer) {
        this->observers.push_back(observer);
    }

    void unregisterObserver(Observer* observer) {
        this->observers.erase(find(this->observers.begin(), this->observers.end(), observer));
    }

    void notify() {
        for (auto observer : this->observers) {
            observer->update();
        }
    }
};
```

### 5. **GUI Layer (`gui/`)**:
The **Qt-based GUI** provides a graphical interface for doctors to manage patients. Doctors can filter patients, add new patients, and update patient information.

---

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or new features.

## License

This project is licensed under the MIT License.
