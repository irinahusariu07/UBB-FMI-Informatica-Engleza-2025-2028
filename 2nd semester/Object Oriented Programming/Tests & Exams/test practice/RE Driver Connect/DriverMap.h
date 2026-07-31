#pragma once
#include "Service.h"
#include<qmessagebox.h>
#include <QMainWindow>
#include "ui_DriverMap.h"
#include<QPainter>

class DriverMap : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	DriverMap(Service&s, QWidget *parent = nullptr);
	~DriverMap();
	void update() override { repaint(); }
	void paintEvent(QPaintEvent* ev) override;

private:
	Ui::DriverMapClass ui;
	Service& service; 
};

