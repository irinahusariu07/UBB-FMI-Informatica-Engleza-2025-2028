#pragma once
#include "StarsListModel.h"
#include<QMessageBox>
#include"Observer.h"
#include"Service.h"
#include <QMainWindow>
#include "ui_AstronomerWindow.h"

class AstronomerWindow : public QMainWindow, public Observer
{
	Q_OBJECT

private:
	Ui::AstronomerWindowClass ui;
	Service& service; 
	StarsListModel* model;
	StarsListModel* listmodel;
	std::string current_constellation;
	std::string astronomer;

public:
	AstronomerWindow(Service& s, const std::string& cc, const std::string& a, QWidget *parent = nullptr);
	~AstronomerWindow();
	void update() override
	{
		model->updateData(service.getStars());
		listmodel->updateData(service.getByName(ui.progressiveName->text().toStdString()));
	}

};

