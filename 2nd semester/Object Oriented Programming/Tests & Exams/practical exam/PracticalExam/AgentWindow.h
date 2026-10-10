#pragma once
#include "ParcelsListView.h"
#include <QMainWindow>
#include "ui_AgentWindow.h"
#include "Service.h"

class AgentWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	AgentWindow(Service& service, const std::string& name, int r, int x, int y, QWidget *parent = nullptr);
	~AgentWindow();
	void update() override { model->updateData(service.getParcelsForDriver(driver)); }

private:
	Ui::AgentWindowClass ui;
	Service& service; 
	std::string driver;
	ParcelsListView* model;
	int ar, ax, ay;
};

