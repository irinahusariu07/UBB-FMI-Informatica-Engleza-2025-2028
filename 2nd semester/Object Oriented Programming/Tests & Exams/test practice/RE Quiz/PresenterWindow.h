#pragma once
#include"Service.h"
#include"QMessageBox"
#include <QMainWindow>
#include "ui_PresenterWindow.h"

class PresenterWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	PresenterWindow(Service& s, QWidget *parent = nullptr);
	~PresenterWindow();
	void update() override { loadData(); }

private:
	Ui::PresenterWindowClass ui;
	Service& service;
	void loadData(); 
};

