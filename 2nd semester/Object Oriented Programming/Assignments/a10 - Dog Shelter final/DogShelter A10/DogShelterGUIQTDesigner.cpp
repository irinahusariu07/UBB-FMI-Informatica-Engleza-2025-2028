#include "DogShelterGUIQTDesigner.h"
#include <QDebug>

DogShelterGUIQTDesigner::DogShelterGUIQTDesigner(QWidget *parent)
    : QMainWindow(parent), service{ nullptr }, repo{ nullptr }, adoptions{ nullptr }, allDogsIndex{ 0 }, filteredDogsIndex{ 0 }
{
    //UNDO REDO SHORTCUTS 
    QShortcut* undoSc = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(undoSc, &QShortcut::activated, this, &DogShelterGUIQTDesigner::undoShortcut);

    QShortcut* redoSc = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(redoSc, &QShortcut::activated, this, &DogShelterGUIQTDesigner::redoShortcut);

    //OPEN 2ND SCREEN FOR USER ADOPTIONS
    QShortcut* openUserListShortcut = new QShortcut(QKeySequence("Ctrl+A"), this);
    connect(openUserListShortcut, &QShortcut::activated, this, [this]() {
        userListWindow->refresh(); 
        userListWindow->show();
        });

    ui.setupUi(this);
    //allow resize when displaying names or breed that are too long
    ui.displayBreed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui.displayName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui.displayAdoptedBreed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui.displayAdoptedName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    //initial display for the tables 
    ui.adminTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.adoptedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //initialize app from page 0 
    ui.stackedWidget->setCurrentIndex(0);
    this->initConnections();
}

DogShelterGUIQTDesigner::~DogShelterGUIQTDesigner()
{
    delete service;
    delete repo; 
    delete adoptions; 
}


//formats the input text to lower and strip spaces 
std::string DogShelterGUIQTDesigner::cleanText(const std::string& text) {
    if (text.empty()) return "";
    size_t start = 0;
    while (start < text.size() && std::isspace(text[start])) start++;
    if (start == text.size()) return "";
    size_t end = text.size() - 1;
    while (end > start && std::isspace(text[end])) end--;

    std::string res = text.substr(start, end - start + 1);
    std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return std::tolower(c); });
    return res;
}



void DogShelterGUIQTDesigner::initConnections()
{
    //page 0 CHOOSE FORMAT
    

    //if CSV button clicked
    connect(ui.csvButton, &QPushButton::clicked, this, [=]() {
        this->repo = new Repo{ "dog_shelter.txt" };
        this->adoptions = new CSVAdoptionList{ "adoption_list.csv" };
        this->service = new Service{ *repo, adoptions };
        //second window for user init with the adoption list 
        userListWindow = new DogListWindow(*service);
        if (this->service->allDogs().empty())
        {
            this->service->addDefaultDogs();
            this->repo->saveToFile();
        }

        ui.stackedWidget->setCurrentIndex(1);
        });

    //if HTML button clicked
    connect(ui.htmlBtn, &QPushButton::clicked, this, [=]() {
        this->repo = new Repo{ "dog_shelter.txt" };
        this->adoptions = new HTMLAdoptionList{ "adoption_list.html" };
        this->service = new Service{ *repo, adoptions };
        //second window for user init with the adoption list 
        userListWindow = new DogListWindow(*service);
        if (this->service->allDogs().empty())
        {
            this->service->addDefaultDogs();
            this->repo->saveToFile();
        }
        ui.stackedWidget->setCurrentIndex(1); //move to next page
        });



    //page 1 CHOOSE MODE 

    //admin mode
    connect(ui.adminModenBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(2); //go to admin page
        });

    //user mode
    connect(ui.userModeBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(7); //go to user page
        });


    //page 2 ADMIN MENU 
    connect(ui.addDogBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(3); //go to add dog page
        });

    connect(ui.listAllBtn, &QPushButton::clicked, this, [=]() {
        this->refreshAdminTable();

        ui.stackedWidget->setCurrentIndex(4); //go to list all dogs page
        });

    connect(ui.removeDogBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(5); //go to remove dog page
        });

    connect(ui.updateDogBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(6); //go to update dog page
        });

    connect(ui.undoBtn, &QPushButton::clicked, this, [=]() {
        try {
            this->service->undo();
            this->refreshAdminTable(); 
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Undo: ", e.what());
        }
        });

    connect(ui.redoBtn, &QPushButton::clicked, this, [=]() {
        try {
            this->service->redo();
            this->refreshAdminTable();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Redo: ", e.what());
        }
        });

    connect(ui.backModesAdminBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(1); //go back to choose mode
        });


    //page 3 ADD DOG PAGE 
    connect(ui.submitAddBtn, &QPushButton::clicked, this, [=]() {
        try
        {
            std::string breed = cleanText(ui.addBreedInput->text().toStdString());
            std::string name = cleanText(ui.addNameInput->text().toStdString());
            int years = ui.addYearsInput->text().toInt();
            int months = ui.addMonthsInput->text().toInt();
            std::string link = cleanText(ui.addLinkInput->text().toStdString());

            this->service->addDog(breed, name, years, months, link);
            ui.addBreedInput->clear();
            ui.addNameInput->clear();
            ui.addYearsInput->clear();
            ui.addMonthsInput->clear();
            ui.addLinkInput->clear();

            ui.stackedWidget->setCurrentIndex(2); //go back to admin menu
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
        }
        });

    connect(ui.cancelAddBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(2); //go back to admin menu
        });

    //page 4 LIST ALL page 
    connect(ui.backAllBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(2); //go back to admin menu
        });


    //page 5 REMOVE DOG page 
    connect(ui.submitRemoveBtn, &QPushButton::clicked, this, [=]() {
        try {
            std::string breed = cleanText(ui.removeBreedInput->text().toStdString());
            std::string name = cleanText(ui.removeNameInput->text().toStdString());

            this->service->removeDog(breed, name);

            ui.removeBreedInput->clear(); 
            ui.removeNameInput->clear();
            ui.stackedWidget->setCurrentIndex(2);
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
        });

    connect(ui.cancelRemoveBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(2); //go back to admin menu
        });


    //page 6 UPDATE DOG PAGE 
    connect(ui.submitUpdateBtn, &QPushButton::clicked, this, [=]() {
        try
        {
            std::string oldBreed = cleanText(ui.oldBreedUpdateInput->text().toStdString());
            std::string oldName = cleanText(ui.oldNameUpdateInput->text().toStdString());
            std::string newBreed = cleanText(ui.breedUpdateInput->text().toStdString());
            std::string newName = cleanText(ui.nameUpdateInput->text().toStdString());
            int years = ui.yearsUpdateInput->text().toInt();
            int months = ui.monthsUpdateInput->text().toInt();
            std::string link = cleanText(ui.linkUpdateInput->text().toStdString());
            this->service->updateDog(oldBreed, oldName, newBreed, newName, years, months, link);

            ui.oldBreedUpdateInput->clear();
            ui.oldNameUpdateInput->clear();
            ui.breedUpdateInput->clear();
            ui.nameUpdateInput->clear();
            ui.yearsUpdateInput->clear();
            ui.monthsUpdateInput->clear();
            ui.linkUpdateInput->clear();
            ui.stackedWidget->setCurrentIndex(2);
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
        }
        });

    connect(ui.cancelUpdateBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(2); //go back to admin menu
        });

    //page 7 USER MODE page
    connect(ui.showAllUserBtn, &QPushButton::clicked, this, [=]() {
        if (this->service)
        {
            this->allDogsList = this->service->allDogs();
            this->allDogsIndex = 0; 
            this->renderAllDogsCarousel();
        }
        ui.stackedWidget->setCurrentIndex(8); //go to dog data + options page
        });

    connect(ui.FilteredUserBtn, &QPushButton::clicked, this, [=]() {
        ui.breedFilterInput->clear(); 
        ui.monthsFilterInput->clear(); ui.yearsFilterInput->clear(); 
        ui.stackedWidget->setCurrentIndex(9); //go to filter criteria page
        });

    connect(ui.showAdoptedUserBtn, &QPushButton::clicked, this, [=]() {
        this->refreshAdoptionTable();
        ui.stackedWidget->setCurrentIndex(11); //go to adoption list page
        });

    connect(ui.backModesUserBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(1); //return to choos user page
        });


    //page 8 SHOW ALL CAROUSEL
    connect(ui.photoBtn, &QPushButton::clicked, this, [=]() {
        if (!allDogsList.empty())
            QDesktopServices::openUrl(QUrl(QString::fromStdString(allDogsList[allDogsIndex].getLink())));
        });

    connect(ui.nextDogBtn, &QPushButton::clicked, this, [=]() {
        if (!allDogsList.empty())
        {
            allDogsIndex = (allDogsIndex + 1) % allDogsList.size();
            this->renderAllDogsCarousel();
        }
        });

    connect(ui.previousDogBtn, &QPushButton::clicked, this, [=]() {
        if (!allDogsList.empty()) {
            allDogsIndex = (allDogsIndex - 1 + allDogsList.size()) % allDogsList.size();
            this->renderAllDogsCarousel();
        }
        });

    connect(ui.adoptDogBtn, &QPushButton::clicked, this, [=]() {
        if (allDogsList.empty()) return;
        try
        {
            Dog target = allDogsList[allDogsIndex];
            this->service->adoptDog(target);
            allDogsList.erase(allDogsList.begin() + allDogsIndex);

            if (this->userListWindow != nullptr) {
                this->userListWindow->refresh();
            }

            if (allDogsList.empty()) {
                QMessageBox::information(this, "Note: ", "You adopted the last available dog!");
            }
            else {
                if (allDogsIndex >= allDogsList.size()) allDogsIndex = 0;
            }
            this->renderAllDogsCarousel();
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Adoption Failure", e.what());
        }
        });

    connect(ui.returnAllUserBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(7); //return to user menu page
        });


    //page 9 FILTERING CRITERIA PAGE
    connect(ui.applyFilterBtn, &QPushButton::clicked, this, [=]() {
        std::string breed = cleanText(ui.breedFilterInput->text().toStdString());
        int maxYears = ui.yearsFilterInput->text().toInt();
        int maxMonths = ui.monthsFilterInput->text().toInt();

        this->filteredDogsList = this->service->filterDogBreedByAge(breed, maxYears, maxMonths);
        this->filteredDogsIndex = 0;
        this->renderFilteredDogsCarousel();

        ui.stackedWidget->setCurrentIndex(10); //go to filtered dogs carousel
        });

    connect(ui.cancelFilterBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(7); //return to user menu
        });


    //page 10 SHOW FILTERED CAROUSEL

    connect(ui.photoFilteredBtn, &QPushButton::clicked, this, [=]() {
        if (!filteredDogsList.empty())
            QDesktopServices::openUrl(QUrl(QString::fromStdString(filteredDogsList[filteredDogsIndex].getLink())));
        });

    connect(ui.nextFilteredBtn, &QPushButton::clicked, this, [=]() {
        if (!filteredDogsList.empty())
        {
            filteredDogsIndex = (filteredDogsIndex + 1) % filteredDogsList.size();
            this->renderFilteredDogsCarousel();
        }
        });

    connect(ui.previousFilteredBtn, &QPushButton::clicked, this, [=]() {
        if (!filteredDogsList.empty()) {
            filteredDogsIndex = (filteredDogsIndex - 1 + filteredDogsList.size()) % filteredDogsList.size();
            this->renderFilteredDogsCarousel();
        }
        });

    connect(ui.adoptFilteredBtn, &QPushButton::clicked, this, [=]() {
        if (filteredDogsList.empty()) return;
        try
        {
            Dog target = filteredDogsList[filteredDogsIndex];
            this->service->adoptDog(target);
            filteredDogsList.erase(filteredDogsList.begin() + filteredDogsIndex);

            if (this->userListWindow != nullptr) {
                this->userListWindow->refresh();
            }

            if (filteredDogsList.empty()) {
                QMessageBox::information(this, "Note: ", "You adopted the last available dog!");
            }
            else {
                if (filteredDogsIndex >= filteredDogsList.size()) filteredDogsIndex = 0;
            }
            this->renderFilteredDogsCarousel();
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Adoption Failure", e.what());
        }
        });

    connect(ui.returnFilteredUserBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(7); //return to user menu page
        });


    //page 11 ADOPTION LIST PAGE 
    connect(ui.displayFormatBtn, &QPushButton::clicked, this, [=]() {
        if (this->service) 
            this->service->openAdoptionFile();
        });

    connect(ui.returnUserAdoptionBtn, &QPushButton::clicked, this, [=]() {
        ui.stackedWidget->setCurrentIndex(7); //return to user menu 
        });
}

void DogShelterGUIQTDesigner::refreshAdminTable()
{
    ui.adminTable->setRowCount(0); //reset all rows in the table to delete old data
    std::vector<Dog> dogs = this->service->allDogs();

    for (auto& d : dogs)
    {
        int r = ui.adminTable->rowCount(); //nr of row
        ui.adminTable->insertRow(r);

        ui.adminTable->setItem(r, 0, new QTableWidgetItem(QString::fromStdString(d.getBreed())));
        ui.adminTable->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(d.getName())));
        ui.adminTable->setItem(r, 2, new QTableWidgetItem(QString::number(d.getAge().getYears())));
        ui.adminTable->setItem(r, 3, new QTableWidgetItem(QString::number(d.getAge().getMonths())));
        ui.adminTable->setItem(r, 4, new QTableWidgetItem(QString::fromStdString(d.getLink())));
    }

    ui.adminTable->resizeColumnsToContents();
}


void DogShelterGUIQTDesigner::refreshAdoptionTable() 
{
    
    ui.adoptedTable->setRowCount(0);
    std::vector<Dog> adoptionsList = this->service->getAdoptionList();

    for (auto& d : adoptionsList) 
    {
        int r = ui.adoptedTable->rowCount();
        ui.adoptedTable->insertRow(r);

        ui.adoptedTable->setItem(r, 0, new QTableWidgetItem(QString::fromStdString(d.getBreed())));
        ui.adoptedTable->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(d.getName())));
        ui.adoptedTable->setItem(r, 2, new QTableWidgetItem(QString::number(d.getAge().getYears())));
        ui.adoptedTable->setItem(r, 3, new QTableWidgetItem(QString::number(d.getAge().getMonths())));
    }

    ui.adoptedTable->resizeColumnsToContents();
}

void DogShelterGUIQTDesigner::renderAllDogsCarousel()
{
    if (allDogsList.empty())
    {
        ui.displayBreed->setText("Breed: -");
        ui.displayName->setText("Name: No dogs");
        ui.displayYears->setText("Years: -");
        ui.displayMonths->setText("Months: -");
        return;
    }

    Dog currentDog = allDogsList[allDogsIndex];
    ui.displayBreed->setText(QString("Breed %1").arg(QString::fromStdString(currentDog.getBreed())));
    ui.displayName->setText(QString("Name: %1").arg(QString::fromStdString(currentDog.getName())));
    ui.displayYears->setText(QString("Years: %1").arg(currentDog.getAge().getYears()));
    ui.displayMonths->setText(QString("Months: %1").arg(currentDog.getAge().getMonths()));
}

void DogShelterGUIQTDesigner::renderFilteredDogsCarousel()
{
    if (filteredDogsList.empty())
    {
        ui.displayAdoptedBreed->setText("Breed: -");
        ui.displayAdoptedName->setText("Name: No dogs");
        ui.displayAdoptedYears->setText("Years: -");
        ui.displayAdoptedMonths->setText("Months: -");
        return;
    }

    Dog currentDog = filteredDogsList[filteredDogsIndex];
    ui.displayAdoptedBreed->setText(QString("Breed %1").arg(QString::fromStdString(currentDog.getBreed())));
    ui.displayAdoptedName->setText(QString("Name: %1").arg(QString::fromStdString(currentDog.getName())));
    ui.displayAdoptedYears->setText(QString("Years: %1").arg(currentDog.getAge().getYears()));
    ui.displayAdoptedMonths->setText(QString("Months: %1").arg(currentDog.getAge().getMonths()));
}

void DogShelterGUIQTDesigner::undoShortcut()
{
    try {
        service->undo();
        refreshAdminTable();
    }
    catch (const ShelterException& e) {
        QMessageBox::warning(this, "Undo", e.what());
    }
}

void DogShelterGUIQTDesigner::redoShortcut()
{
    try {
        service->redo();
        refreshAdminTable();
    }
    catch (const ShelterException& e) {
        QMessageBox::warning(this, "Redo", e.what());
    }
}