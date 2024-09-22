#ifndef GUI_H
#define GUI_H

#include <QWidget>

#include "service/service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit gui(QWidget *parent = nullptr, Service *service = nullptr, Doctor *doctor = nullptr);
    ~gui() override;

private:
    Ui::gui *ui;

    Service *service;
    Doctor *doctor;

    void updateList();
    void updateMyPatients();
    void addPatient();
    void updatePatients();
    void update() override;
};


#endif //GUI_H
