#include <QApplication>
#include <QPushButton>
#include "gui.h"
#include "repository/repository.h"
#include "service/service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo;
    Service service(&repo);
    for(Doctor *doctor: service.getDoctorsFromRepo()) {
        auto g = new gui(nullptr, &service, doctor);
        g->show();
    }
    return QApplication::exec();
}
