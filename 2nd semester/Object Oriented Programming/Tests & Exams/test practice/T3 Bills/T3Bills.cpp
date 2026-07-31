#include "T3Bills.h"

T3Bills::T3Bills(Service* service, QWidget* parent)
    : QMainWindow(parent), service{ service }
{
    ui.setupUi(this);
    ui.displayTotal->setReadOnly(true);
    this->initConnections();
    this->displayList(this->service->getAll());
}

T3Bills::~T3Bills()
{
}

void T3Bills::initConnections()
{
    connect(ui.showBtn, &QPushButton::clicked, this, [=] {
        std::string input = ui.statusOption->text().toLower().toStdString();
        std::vector<Bills> subset;
        if (input == "paid") subset = this->service->getBillsStatus(true);
        else if (input == "unpaid") subset = this->service->getBillsStatus(false);
        else if (input == "all" || input.empty()) subset = this->service->getAll();
        else {
            ui.billList->clear();
            return;
        }
        this->displayList(subset);
        });

    connect(ui.totalBtn, &QPushButton::clicked, this, [=] {
        std::string input = ui.choseCompany->text().toLower().toStdString();
        try {
            double total = service->totalSum(input);
            ui.displayTotal->setText(QString::number(total));
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
            ui.displayTotal->clear();
        }
        ui.choseCompany->clear();
        });
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! + display in table 
void T3Bills::displayList(std::vector<Bills> to_display)
{
    ui.billList->clear();
    for (auto& b : to_display)
    {
        QString rowText = QString::fromStdString(b.GUItoString());
        QListWidgetItem* item = new QListWidgetItem(rowText);
        if (!b.getStatus())
        {
            item->setBackground(QBrush(QColor("red")));
            item->setForeground(QBrush(QColor("white")));
        }
        ui.billList->addItem(item);
    }
}

