#pragma once
#include"Service.h"
#include"BacteriaList.h"
#include <QtWidgets/QMainWindow>
#include "ui_REMicrobialWorld.h"
#include<qmessagebox.h>

class REMicrobialWorld : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    REMicrobialWorld(Service& s, Biologist bio, QWidget *parent = nullptr);
    ~REMicrobialWorld();
    void update() override { model->updateData(service.getBacteriaForBiologist(biolog.getStudied()));}

private:
    Ui::REMicrobialWorldClass ui;
    Service& service; 
    Biologist biolog; 
    BacteriaList* model;
};

