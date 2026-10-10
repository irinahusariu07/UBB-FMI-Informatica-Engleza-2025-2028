#pragma once
#include "ParcelsListView.h"
#include"Service.h"
#include <QMainWindow>
#include "ui_LogisticsDashboard.h"
#include <qmessagebox.h>


class LogisticsDashboard : public QMainWindow, public Observer
{
	Q_OBJECT
private:
	Ui::LogisticsDashboardClass ui;
	Service& service;
	ParcelsListView* model;

public:
	LogisticsDashboard(Service& s, QWidget *parent = nullptr);
	~LogisticsDashboard();
	void update() { model->updateData(service.getParcels()); }


};

