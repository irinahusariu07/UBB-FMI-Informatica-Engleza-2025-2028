#include "LogisticsDashboard.h"

LogisticsDashboard::LogisticsDashboard(Service& s, QWidget* parent)
	: QMainWindow(parent), service{ s }
{
	ui.setupUi(this);
	service.registerObserver(this);
	model = new ParcelsListView(service.getParcels());
	ui.tableView->setModel(model);

	connect(ui.addBtn, &QPushButton::clicked, this, [=]() {
		try
		{
			std::string rec, street, num, x, y;
			rec = ui.recipientInput->text().toStdString();
			street = ui.streetInput->text().toStdString();
			num = ui.numberInput->text().toStdString();
			int n = std::stoi(num);
			x = ui.xcInput->text().toStdString();
			y = ui.ycInput->text().toStdString();
			int xi = std::stoi(x);
			int yi = std::stoi(y);
			service.addParcel(rec, street, n, xi, yi);  
		}
		catch (std::exception& e)
		{
			QMessageBox::critical(this, "Error: ", e.what());
		}
		});
	this->update();
}

LogisticsDashboard::~LogisticsDashboard()
{}

