#pragma once
#include"PatientModel.h"
#include"Service.h"
#include<QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_REPatientManagement.h"

class REPatientManagement : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    REPatientManagement(Service& srv, const std::string& doc, QWidget *parent = nullptr);
    ~REPatientManagement();
    void update() override { model->updateData(service.sortByDates(service.getSpecialisationPatients(service.getDocByName(doctor)))); }

private:
    Ui::REPatientManagementClass ui;
    Service& service; 
    std::string doctor; 
    PatientModel* model; 
};


