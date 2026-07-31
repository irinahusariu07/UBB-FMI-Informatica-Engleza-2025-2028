#include "DriverMap.h"


DriverMap::DriverMap(Service& s, QWidget* parent)
	: QMainWindow(parent), service(s)
{
	ui.setupUi(this);
	service.registerObs(this);
}

DriverMap::~DriverMap()
{}

void DriverMap::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);

	for (auto& d : service.getDrivers())
	{
		painter.setBrush("red");
		painter.drawEllipse(QPoint(d.getLatit()*100, d.getLongit()*100), 10, 10);
		painter.drawText((d.getLatit()*100 + 10), (d.getLongit()*100 + 10),
			QString::fromStdString(d.getName() + " lat: " + std::to_string(d.getLatit()) + " long: " + std::to_string(d.getLongit())));
	}
}

