#pragma once
#include <QtWidgets/QMainWindow>
#include<QMessageBox>
#include "ui_Test3.h"
#include"Service.h"

class Test3 : public QMainWindow
{
    Q_OBJECT

public:
    Test3(Service* s, QWidget *parent = nullptr);
    ~Test3();

private:
    Ui::Test3Class ui;
    Service* service;
    void initConnections(); 
    void displayList(std::vector<Airport> to_display); 
};

