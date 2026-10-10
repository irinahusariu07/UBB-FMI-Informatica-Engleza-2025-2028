#pragma once
#pragma once
#include "Service.h"
#include "Repo.h"
#include "AdoptionList.h"
#include <vector>
#include <string>
#include <QtWidgets/QMainWindow>
#include "ui_DogShelterGUIQTDesigner.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <algorithm>
#include <cctype>

class DogShelterGUIQTDesigner : public QMainWindow
{
    Q_OBJECT

public:
    DogShelterGUIQTDesigner(QWidget *parent = nullptr);
    ~DogShelterGUIQTDesigner();

private:
    Ui::DogShelterGUIQTDesignerClass ui;
    Service* service;
    Repo* repo;
    AdoptionList* adoptions;

    //one by one navigation for show all and show filtered
    int allDogsIndex;
    std::vector<Dog> allDogsList;

    int filteredDogsIndex;
    std::vector<Dog> filteredDogsList;

    
    void initConnections();
    void refreshAdminTable();
    void refreshAdoptionTable();
    void renderAllDogsCarousel();
    void renderFilteredDogsCarousel();
    std::string cleanText(const std::string& text); //input formatting strip and lower 
};

