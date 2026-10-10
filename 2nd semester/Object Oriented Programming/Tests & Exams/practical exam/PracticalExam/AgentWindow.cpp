#include "AgentWindow.h"
#include "QModelIndex"
#include"QMessageBox"


AgentWindow::AgentWindow(Service& service, const std::string& name, int c, int x, int y, QWidget *parent)
	: QMainWindow(parent), service{ service }, driver{ name }, ar{c}, ax{x}, ay{y}
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString("Agent: " + driver));
	service.registerObserver(this);
	model = new ParcelsListView(service.getParcelsForDriver(driver));
	ui.label->setText(QString::fromStdString("Agent: " + driver + "Center: (" + std::to_string(ax) + "," + std::to_string(ay) + ") Radius: " + std::to_string(ar)));
	ui.tableView->setModel(model);

	connect(ui.deliverBtn, &QPushButton::clicked, this, [=]() {
		QModelIndex selected = ui.tableView->selectionModel()->currentIndex();
		if (!selected.isValid()) return;
		std::string rec = selected.sibling(selected.row(), 0).data().toString().toStdString();
		try{ this->service.deliverParcel(rec); }
		catch(std::exception & e)
		{
			QMessageBox::critical(this, "Error: ", e.what());
		}
		});
}

AgentWindow::~AgentWindow()
{}

