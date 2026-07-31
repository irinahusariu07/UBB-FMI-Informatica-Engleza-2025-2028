#pragma once
#include"Service.h"
#include<qmessagebox.h>
#include <QMainWindow>
#include "ui_AdminWindow.h"

class AdminWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	AdminWindow(Service& serv, User& u, QWidget* parent = nullptr);
	~AdminWindow();
	void update() override { loadData(); }

private:
	Ui::AdminWindowClass ui;
	Service& service;
	User& user;
	void loadData();
};