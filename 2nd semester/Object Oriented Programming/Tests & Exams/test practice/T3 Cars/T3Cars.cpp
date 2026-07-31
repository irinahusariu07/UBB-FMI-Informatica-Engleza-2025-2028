#include "T3Cars.h"

T3Cars::T3Cars(Service* s, QWidget* parent)
    : QMainWindow(parent), service{ s }
{
    ui.setupUi(this);
    ui.manufacturerLE->setReadOnly(true);
    ui.nrCarsLE->setReadOnly(true);
    this->displayList(service->getAll());
    this->initConnections();
}

T3Cars::~T3Cars()
{}

void T3Cars::initConnections()
{
    connect(ui.showAllBtn, &QPushButton::clicked, this, [=] {
        ui.llistWidget->clear(); 
        this->displayList(service->getAll());
        });

    connect(ui.showManBtn, &QPushButton::clicked, this, [=] {
        std::string input = ui.inputLE->text().toLower().toStdString(); //citesc manuf
        std::vector<Car> by_manuf = service->getCarsFromManufacturer(input); //procesez si trb sa le afisez in lista si in widget
        ui.nrCarsLE->setText(QString::number(by_manuf.size())); //am pus nr 
        //ui.llistWidget->clear();
        this->displayList(by_manuf);
        });
}

void T3Cars::displayList(std::vector<Car> to_display)
{
    ui.llistWidget->clear();
    for (auto& c : to_display)
    {
        QString rowText = QString::fromStdString(c.GUItoString());
        QListWidgetItem* item = new QListWidgetItem(rowText);

        item->setForeground(QBrush(QColor(QString::fromStdString(c.getColor()))));
        ui.llistWidget->addItem(item);
    }
}




