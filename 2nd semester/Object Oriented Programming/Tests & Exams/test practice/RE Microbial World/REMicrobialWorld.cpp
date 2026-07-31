#include "REMicrobialWorld.h"

REMicrobialWorld::REMicrobialWorld(Service& s, Biologist bio, QWidget *parent)
    : QMainWindow(parent), service{s}, biolog{bio}
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(biolog.getName())); 
    service.registerObs(this); 
    model = new BacteriaList(service.getBacteriaForBiologist(biolog.getStudied())); 
    ui.tableView->setModel(model); 

    ui.comboBox->addItem("ALL"); 
    for (auto& b : service.getBacteriaForBiologist(biolog.getStudied()))
    {
        ui.comboBox->addItem(QString::fromStdString(b.getSpecies()));
    }

    connect(ui.comboBox, &QComboBox::currentIndexChanged, this, [=](int idx)
        {
            QString selected = ui.comboBox->itemText(idx); 
            if (selected == "ALL") model->updateData(service.getBacteriaForBiologist(biolog.getStudied()));
            else model->updateData(service.filterSpecies(selected.toStdString()));
        });

    connect(ui.addBtn, &QPushButton::clicked, this, [=]()
        {
            std::string name = ui.nameInput->text().toStdString();
            std::string spec = ui.speciesInput->text().toStdString(); 
            int size = ui.speciesInput->text().toInt(); 
            std::string dis = ui.diseaseInput->text().toStdString(); 

            try
            {
                service.addBacteria(name, spec, size, dis); 
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "Error: ", e.what()); 
            }
        });

    connect(ui.disBtn, &QPushButton::clicked, this, [=]()
        {
            std::string name = ui.nameInput->text().toStdString();
            std::string spec = ui.speciesInput->text().toStdString();
            try
            {
                std::vector<std::string> dis = service.getDiseases(name, spec); 
                ui.listWidget->clear();
                for (auto& d : dis)
                {
                    ui.listWidget->addItem(QString::fromStdString(d));
                }
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "Error: ", e.what());
            }
        });

    connect(ui.addDisBtn, &QPushButton::clicked, this, [=]()
        {
            std::string name = ui.nameInput->text().toStdString();
            std::string spec = ui.speciesInput->text().toStdString();
            std::string dis = ui.diseaseInput->text().toStdString();
            try
            {
                service.addDisease(name, spec, dis);
                emit ui.disBtn->clicked();
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "Error: ", e.what());
            }

        });
}

REMicrobialWorld::~REMicrobialWorld()
{}

