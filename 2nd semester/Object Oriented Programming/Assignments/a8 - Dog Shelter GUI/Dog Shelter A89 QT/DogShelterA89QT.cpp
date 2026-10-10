#include "DogShelterA89QT.h"

DogShelterA89QT::DogShelterA89QT(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    r = new Repo{ "dog_shelter.txt" };
    adoptions = new CSVAdoptionList{ "adoption_list.csv" };
    s = new Service{ *r, adoptions }; 

    //create the central widget and the vertical layout 
    central = new QWidget{ this };
    mainLayout = new QVBoxLayout{ central }; 
    this->setCentralWidget(central);  

    //initialize the stack that will be useful in changing between pages and modes
    stack = new QStackedWidget{ this };
    mainLayout->addWidget(stack);


    //the selection page - user or admin 
    selectionPage = new QWidget();
    QVBoxLayout* selectionLayout = new QVBoxLayout(selectionPage);
    
    //the welcome message 
    QLabel* welcomeLabel = new QLabel("Welcome to our Dog Shelter! Choose your mode:");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    //the main page structure 
    adminBtn = new QPushButton{ "Admin Mode" };
    userBtn = new QPushButton{ "User Mode" };
    selectionLayout->addWidget(welcomeLabel);
    selectionLayout->addWidget(adminBtn);
    selectionLayout->addWidget(userBtn);
    stack->addWidget(selectionPage); //push it to the stack at idx 0

    
    //second page idx 1 
    adminPage = new QWidget();
    QVBoxLayout* adminLayout = new QVBoxLayout(adminPage);


    //create the table for dog data 
    table = new QTableWidget{};
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({ "Breed", "Name", "Years", "Months", "Link" });
    adminLayout->addWidget(table);

    //horizontal layout for functionalities buttons - add and remove 
    QHBoxLayout* adminBtnLayout = new QHBoxLayout{};
    addBtn = new QPushButton{ "Add Dog" };
    removeBtn = new QPushButton{ "Remove Dog" };
    adminBtnLayout->addWidget(addBtn);
    adminBtnLayout->addWidget(removeBtn);
    adminLayout->addLayout(adminBtnLayout);

    stack->addWidget(adminPage); //push page on stack idx 1 


    //third page user mode idx 2 
    userPage = new QWidget();
    QVBoxLayout* userLayout = new QVBoxLayout(userPage);
    userLayout->addWidget(new QLabel{ "User Mode: Browse and Adopt Dogs" });

    stack->addWidget(userPage); //push it to the stack 

    //make the pages switchable when clicking buttons 
    //show admin page
    connect(adminBtn, &QPushButton::clicked, this, [=]() {
        stack->setCurrentIndex(1);
        });

    //show user page 
    connect(userBtn, &QPushButton::clicked, this, [=]() {
        stack->setCurrentIndex(2);
        });

    //load dog data into the table 
    this->loadData();
}

DogShelterA89QT::~DogShelterA89QT()
{
    delete s; 
    delete r;
    delete adoptions;
}

void DogShelterA89QT::loadData()
{
    //clear the table
    this->table->setRowCount(0);

    //get the data from service
    std::vector<Dog> dogs = this->s->allDogs();

    for (auto& d : dogs) {
        int currentRow = this->table->rowCount();
        this->table->insertRow(currentRow);

        //convert data to qstring and insert into cells
        this->table->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(d.getBreed())));
        this->table->setItem(currentRow, 1, new QTableWidgetItem(QString::fromStdString(d.getName())));
        this->table->setItem(currentRow, 2, new QTableWidgetItem(QString::number(d.getAge().getYears())));
        this->table->setItem(currentRow, 3, new QTableWidgetItem(QString::number(d.getAge().getMonths())));
        this->table->setItem(currentRow, 4, new QTableWidgetItem(QString::fromStdString(d.getLink())));
    }

    //resize cols to fit data 
    this->table->resizeColumnsToContents();
}

