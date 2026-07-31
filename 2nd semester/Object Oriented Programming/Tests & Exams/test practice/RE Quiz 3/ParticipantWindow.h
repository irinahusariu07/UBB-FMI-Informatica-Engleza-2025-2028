#pragma once
#include"Service.h"
#include<QMessageBox>
#include <QMainWindow>
#include "ui_ParticipantWindow.h"

class ParticipantWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	ParticipantWindow(Service&s, Participant pa, QWidget *parent = nullptr);
	~ParticipantWindow();
	void update() override { loadData(); }

private:
	Ui::ParticipantWindowClass ui;
	Service& service; 
	Participant particip; 
	void loadData();
	std::unordered_set<int> answered;
};

