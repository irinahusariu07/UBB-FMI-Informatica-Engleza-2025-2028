#pragma once
#include "Service.h"
#include <QtWidgets/QMainWindow>
#include "ui_T3Cars.h"

class T3Cars : public QMainWindow
{
    Q_OBJECT

public:
    T3Cars(Service* s, QWidget *parent = nullptr);
    ~T3Cars();

private:
    Ui::T3CarsClass ui;
    Service* service; 
    void initConnections();
    void displayList(std::vector<Car> to_display); 
};

