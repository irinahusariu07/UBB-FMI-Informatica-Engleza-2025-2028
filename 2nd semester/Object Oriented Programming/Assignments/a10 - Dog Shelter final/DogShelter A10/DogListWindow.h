#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>  
#include "Service.h"
#include"DogListModel.h"

class DogListWindow : public QWidget
{
    Q_OBJECT

private:
    QTableView* table;
    Service& service;
    DogListModel* model;

public:
    DogListWindow(Service& s, QWidget* parent = nullptr)
        : QWidget(parent), service(s)
    {
        //layout for table 
        QVBoxLayout* layout = new QVBoxLayout(this);
        table = new QTableView(this);

        //instantiate model -> pass adoption list (create table entity)
        model = new DogListModel(service.getAdoptionList(), this);
        table->setModel(model);

        //user shouldnt be able to edit 
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->resizeColumnsToContents();

        //add table to layout
        layout->addWidget(table);
        this->setLayout(layout);

        setWindowTitle("Adoption List View (Model/View)");
        resize(600, 400);
    }

    //called whenever a modif is made 
    void refresh() {
        model->updateData(service.getAdoptionList()); //get a copy of current adoption list 
        table->resizeColumnsToContents();
    }
};