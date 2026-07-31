#include "REDriverConnect.h"

REDriverConnect::REDriverConnect(Service& s, Driver& d, QWidget *parent)
    : QMainWindow(parent), service{s}, driver{d}
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(driver.getName()));
    service.registerObs(this);

    updateUi();
    loadData();


    connect(ui.addBtn, &QPushButton::clicked, this, [=]()
        {
            std::string desc = ui.descInput->text().toStdString();
            int lat = ui.latInput->text().toInt();
            int lon = ui.lonInput->text().toInt();

            try
            {
                service.addReport(desc, driver.getName(), lat, lon, driver.getLatit(), driver.getLongit());
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "Error: ", e.what());
            }
        });

    connect(ui.validateBtn, &QPushButton::clicked, this, [=]()
        {
            std::string desc = ui.descInput->text().toStdString();
            int lat = ui.latInput->text().toInt();
            int lon = ui.lonInput->text().toInt();
            try
            {
                service.validateReport(desc, lat, lon, driver.getName());
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "Error: ", e.what());
            }

        });
}

REDriverConnect::~REDriverConnect()
{}

void REDriverConnect::loadData()
{
    std::vector<Report> data = service.getAllInRadius(driver.getLatit(), driver.getLongit(), 10);
    ui.listWidget->clear();
    for (auto& d : data)
    {
        ui.listWidget->addItem(QString::fromStdString(d.getDesc() + " | " + d.getReporter() + " | " +
            std::to_string(d.getLatit()) + " | " + std::to_string(d.getLongit()) + " | " + d.getValid()));
    }
}

void REDriverConnect::updateUi()
{
    //set label 
    ui.latLabel->setText(QString::number(driver.getLatit()));
    ui.longLabel->setText(QString::number(driver.getLongit()));
    ui.scoreLabel->setText(QString::number(driver.getScore()));
    ui.statusLabel->setText(QString::fromStdString(driver.getStatus()));

    if (driver.getScore() < 10) driver.setStatus("baby");
    else if (driver.getScore() >= 10 && driver.getScore() < 15) driver.setStatus("grownup");
    else if (driver.getScore() >= 15) driver.setStatus("knight");

    if (driver.getStatus() == "baby") this->setStyleSheet("background-color: pink");
    else if (driver.getStatus() == "grownup") this->setStyleSheet("background-color: orange");
    else if (driver.getStatus() == "knight") this->setStyleSheet("background-color: blue");
}

