#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_T3Bills.h"
#include "Service.h"

class T3Bills : public QMainWindow
{
    Q_OBJECT

public:
    T3Bills(Service* s, QWidget *parent = nullptr);
    ~T3Bills();

private:
    Ui::T3BillsClass ui;
    Service* service; 
    void initConnections();
    void displayList(std::vector<Bills>to_display);
};

