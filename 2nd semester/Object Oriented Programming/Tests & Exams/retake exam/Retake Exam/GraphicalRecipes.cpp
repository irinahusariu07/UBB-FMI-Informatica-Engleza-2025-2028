#include "GraphicalRecipes.h"

GraphicalRecipes::GraphicalRecipes(Service&s, QWidget *parent)
	: QMainWindow(parent), service{s}
{
	ui.setupUi(this);
	service.registerObs(this);
}

GraphicalRecipes::~GraphicalRecipes()
{}

void GraphicalRecipes::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this); 

	int startX = 100, startY = 100;
	for (auto& r : service.getAllSorted())
	{
		if (r.getTime() > 100) painter.setBrush(QBrush("red"));
		else painter.setBrush(QBrush("blue")); 
		painter.drawEllipse(QPoint(startX, startY), r.getTime() / 5, r.getTime() / 5);
		painter.drawText(startX + 5, startY +5, QString::fromStdString(r.getName()));
		startX += 50; 
		startY += 50;
	}
}

