#pragma once
#include <QMainWindow>
#include <QTableView>
#include "IssueListModel.h"
#include "Observer.h"
#include "Service.h"
#include "ui_ProgrammerWindow.h"
#include<qmessagebox.h>

class ProgrammerWindow : public QMainWindow, public Observer
{
    Q_OBJECT

private:
    Ui::ProgrammerWindowClass ui;
    Service& service;
    IssueListModel* model;
    std::string programmerName;

public:
    ProgrammerWindow(Service& s, const std::string& name, QWidget* parent = nullptr) : QMainWindow(parent), service{ s }, programmerName{ name }
    {
        ui.setupUi(this);
        this->setWindowTitle(QString::fromStdString("Name: " + name));
        ui.pname->setText(QString::fromStdString("Programmer: " + name));
        service.registerObserver(this);
        model = new IssueListModel(service.getIssues());
        ui.issueTable->setModel(model);

        connect(ui.resolveBtn, &QPushButton::clicked, this, [=]
            {
                std::string desc = ui.descriptionInput->text().toStdString();
                try
                {
                    service.resolveIssue(desc, programmerName);
                }
                catch (std::exception& e)
                {
                    QMessageBox::critical(this, "Error: ", e.what());
                }
            });

        connect(ui.removeBtn, &QPushButton::clicked, this, [=] 
            {
                std::string desc = ui.descriptionInput->text().toStdString();
                try
                {
                    service.removeIssue(desc);
                }
                catch (std::exception& e)
                {
                    QMessageBox::critical(this, "Error: ", e.what());
                }
            });

    }

    void update() override {
        model->updateData(service.getIssues());
    } 
    ~ProgrammerWindow() {}
};