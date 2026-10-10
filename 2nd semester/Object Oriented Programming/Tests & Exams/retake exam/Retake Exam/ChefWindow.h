#pragma once
#include"Service.h"
#include<qmessagebox.h>
#include <QMainWindow>
#include "ui_ChefWindow.h"

class ChefWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	ChefWindow(Service&s, Chef c, QWidget *parent = nullptr);
	~ChefWindow();
	void update() override { loadData(); }

private:
	Ui::ChefWindowClass ui;
	Service& service; 
	Chef chef; 
	void loadData(); 
};

