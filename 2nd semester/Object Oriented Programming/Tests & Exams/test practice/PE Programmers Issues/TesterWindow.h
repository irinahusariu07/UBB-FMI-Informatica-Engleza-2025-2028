#pragma once
#include <QMainWindow>
#include <QTableView>
#include "IssueListModel.h"
#include "Observer.h"
#include "Service.h"
#include "ui_TesterWindow.h"
#include<qmessagebox.h>

class TesterWindow : public QMainWindow, public Observer
{
	Q_OBJECT

private:
	Ui::TesterWindowClass ui;
	Service& service;
	IssueListModel* model;
	std::string testerName;

public:
	TesterWindow(Service& s, const std::string& name, QWidget* parent = nullptr) : QMainWindow(parent), service{ s }, testerName{ name }
	{
		ui.setupUi(this);
		this->setWindowTitle(QString::fromStdString("Name: " + name));
		ui.tname->setText(QString::fromStdString("Tester: " + name));

		service.registerObserver(this);
		model = new IssueListModel(service.getIssues());
		ui.issueTable->setModel(model);

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

		connect(ui.addBtn, &QPushButton::clicked, this, [=]
			{
				std::string desc = ui.descriptionInput->text().toStdString();
				try
				{
					service.addIssue(desc, testerName);
				}
				catch(std::exception&e)
				{
					QMessageBox::critical(this, "Error: ", e.what());
				}
			});

	}

	void update() override {
		model->updateData(service.getIssues());
	}

	~TesterWindow() {}

};
