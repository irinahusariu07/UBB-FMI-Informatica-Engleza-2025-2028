#pragma once
#include<QPainter>
#include <QMainWindow>
#include "ui_GraphicalRecipes.h"
#include"Service.h"

class GraphicalRecipes : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	GraphicalRecipes(Service&s, QWidget *parent = nullptr);
	~GraphicalRecipes();
	void update() override { repaint(); }
	void paintEvent(QPaintEvent* ev) override;

private:
	Ui::GraphicalRecipesClass ui;
	Service& service; 
};

