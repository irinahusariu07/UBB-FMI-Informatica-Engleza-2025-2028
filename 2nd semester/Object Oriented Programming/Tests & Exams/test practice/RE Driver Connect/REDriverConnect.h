#pragma once
#include"Service.h"
#include<QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_REDriverConnect.h"

class REDriverConnect : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    REDriverConnect(Service&s, Driver& d, QWidget *parent = nullptr);
    ~REDriverConnect();
    void update() override { loadData(); updateUi(); }

private:
    Ui::REDriverConnectClass ui;
    Service& service; 
    Driver& driver; 
    void loadData(); 
    void updateUi();

};

