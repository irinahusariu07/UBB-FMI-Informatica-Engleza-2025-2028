#pragma once
#include"Service.h"
#include"IdeaList.h"
#include<qmessagebox.h>
#include <QtWidgets/QMainWindow>
#include "ui_REScreenWriter.h"

class REScreenWriter : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    REScreenWriter(Service& ser, Writer w, const std::string& epfile, QWidget *parent = nullptr);
    ~REScreenWriter();

    void update() override { model->updateData(service.getIdeasSorted()); }

private:
    Ui::REScreenWriterClass ui;
    Service& service; 
    Writer writer; 
    IdeaList* model; 
    std::string episode_file;
};

