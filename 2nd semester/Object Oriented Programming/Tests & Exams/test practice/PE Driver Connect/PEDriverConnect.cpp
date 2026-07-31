#include "PEDriverConnect.h"

PEDriverConnect::PEDriverConnect(Service& s, const std::string& name, int clat, int clong, int score, QWidget* parent)
    : QMainWindow(parent), service{ s }, driver{ name }, clat{clat}, clong{clong}, score{score}
{
    ui.setupUi(this);
    service.registerOserver(this);
    this->setWindowTitle(QString::fromStdString(driver));
    ui.label->setText(QString::fromStdString("Driver: " + driver + "\nLAT: " + std::to_string(clat) + " LONG: " + std::to_string(clong) + "\nSCORE: " + std::to_string(score)));
    model = new ReportListModel(service.getReports());
    ui.tableView->setModel(model);

    connect(ui.addBtn, &QPushButton::clicked, this, [=]() {
        try {
            std::string desc;
            int lat, longi;
            desc = ui.descInput->text().toStdString();
            lat = ui.latInput->text().toInt();
            longi = ui.longInput->text().toInt();
            service.addReport(desc, driver, lat, longi, false);
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
        }
        });

    connect(ui.validateBtn, &QPushButton::clicked, this, [=]() {
        try {
            std::string desc;
            int lat, longi;
            desc = ui.descInput->text().toStdString();
            lat = ui.latInput->text().toInt();
            longi = ui.longInput->text().toInt();
            service.validateReport(desc, lat, longi, driver);
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
        }
        });
}


PEDriverConnect::~PEDriverConnect()
{}

