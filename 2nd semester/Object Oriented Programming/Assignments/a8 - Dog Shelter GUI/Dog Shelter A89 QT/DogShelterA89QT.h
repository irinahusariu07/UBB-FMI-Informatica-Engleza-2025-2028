#pragma once
#include"Service.h"
#include"Repo.h"
#include"AdoptionList.h"
#include"CSVAdoptionList.h"
#include"HTMLAdoptionList.h"
#include <QStackedWidget>
#include <QtWidgets/QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
//#include "ui_DogShelterA89QT.h"

class DogShelterA89QT : public QMainWindow
{
    Q_OBJECT

public:
    DogShelterA89QT(QWidget *parent = nullptr);
    ~DogShelterA89QT();

private:
    //Ui::DogShelterA89QTClass ui;
    Service* s; 
    Repo* r; 
    AdoptionList* adoptions; 


    QWidget* central; //main container widget 
    QVBoxLayout* mainLayout; //vertical layout 
    QTableWidget* table; //list all in a table
    QWidget* selectionPage; //initial screen -> choose mode

    QPushButton* addBtn; //add button 
    QPushButton* removeBtn; //remove button 
    QStackedWidget* stack; //switching between screens 
    QWidget* adminPage; //admin page idx 1 
    QWidget* userPage; //user page idx 2

    QPushButton* adminBtn; //button to choose admin mode 
    QPushButton* userBtn; //button to choose user mode 

    void loadData(); //puts data in the table
};

