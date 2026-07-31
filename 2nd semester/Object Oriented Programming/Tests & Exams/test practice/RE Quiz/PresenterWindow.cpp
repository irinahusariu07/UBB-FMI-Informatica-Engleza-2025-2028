#include "PresenterWindow.h"

PresenterWindow::PresenterWindow(Service& s, QWidget* parent)
	: QMainWindow(parent), service{ s }
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString("PRESENTER"));
	service.registerObs(this);
	loadData();
}

PresenterWindow::~PresenterWindow()
{}

void PresenterWindow::loadData()
{
	ui.listWidget->clear(); 
	for (auto& q : service.getAllID())
	{
		ui.listWidget->addItem(QString::fromStdString(std::to_string(q.getId()) + ". " + q.getText() + " -> " + q.getAnswer() + std::to_string(q.getScore())));
	}
}

