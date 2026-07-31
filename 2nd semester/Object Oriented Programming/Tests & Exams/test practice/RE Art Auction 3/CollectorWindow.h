#pragma once
#include"Service.h"
#include <QMainWindow>
#include "ui_CollectorWindow.h"
#include<qmessagebox.h>

class CollectorWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	CollectorWindow(Service& ser, User usr, QWidget* parent = nullptr);
	~CollectorWindow();
	void update() override { loadDataMain(); }

private:
	Ui::CollectorWindowClass ui;
	Service& service;
	User user;
	void loadDataMain();
};