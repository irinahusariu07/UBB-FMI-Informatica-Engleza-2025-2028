#pragma once
#include "ReportsListModel.h"
#include <QtWidgets/QMainWindow>
#include "ui_PEDriverConnect.h"
#include"Service.h"
#include<qmessagebox.h>

class PEDriverConnect : public QMainWindow, public Observer
{
    Q_OBJECT
private:
    Ui::PEDriverConnectClass ui;
    Service& service; 
    ReportListModel* model;
    std::string driver; 
    int clat, clong, score;

public:
    PEDriverConnect(Service& s, const std::string&name, int clat, int clong, int score, QWidget* parent);
    void update() override { model->updateDate(service.getReports()); }
    ~PEDriverConnect();

};

