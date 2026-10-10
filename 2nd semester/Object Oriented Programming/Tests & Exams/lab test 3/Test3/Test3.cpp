#include "Test3.h"

Test3::Test3(Service*s, QWidget *parent): QMainWindow(parent), service{s}
{
    ui.setupUi(this);
    ui.totalDelay->setReadOnly(true);

    this->initConnections(); 
    this->displayList(service->getAll()); 
}

Test3::~Test3()
{}

void Test3::initConnections()
{
    connect(ui.delayBtn, &QPushButton::clicked, this, [=] {
        std::string input = ui.inputDelay->text().toStdString(); 
        int min_delay = stoi(input); 
        std::vector<Airport> to_display = service->getWithDelay(min_delay);
        this->displayList(to_display);
        });

    connect(ui.hourBtn, &QPushButton::clicked, this, [=] {
        try {
            std::string destination, shour;
            destination = ui.inputDestination->text().toLower().toStdString();
            shour = ui.inputHour->text().toStdString();
            int hour = stoi(shour);
            std::vector<Airport> to_display = service->getAfterHour(hour); 
            this->displayList(to_display);

        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Note: ", e.what());
        }
        });
}

void Test3::displayList(std::vector<Airport> to_display)
{
    ui.listWidget->clear();
    for (auto& a : to_display)
    {
        QString rowText = QString::fromStdString(a.GUItoString());
        QListWidgetItem* item = new QListWidgetItem(rowText);

        ui.listWidget->addItem(item);
    }
}

