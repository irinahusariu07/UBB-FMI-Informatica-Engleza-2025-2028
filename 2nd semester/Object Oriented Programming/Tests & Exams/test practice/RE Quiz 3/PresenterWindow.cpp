#include "PresenterWindow.h"

PresenterWindow::PresenterWindow(Service& s, QWidget* parent)
	: QMainWindow(parent), service{ s }
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString("PRESENTER"));
	service.registerObs(this);
	loadData();

	connect(ui.addBtn, &QPushButton::clicked, this, [=]()
	{
		std::string txt, ans; 
		int score, id; 
		txt = ui.txtInput->text().toStdString();
		ans = ui.ansInput->text().toStdString();
		score = ui.scoreInput->text().toInt();
		id = ui.idInput->text().toInt();
		try
		{
			service.addQuestion(id, txt, ans, score);
		}
		catch (std::exception& e)
		{
			QMessageBox::critical (this, "Error: ", e.what());
		}
	});

}

PresenterWindow::~PresenterWindow()
{
}

void PresenterWindow::loadData()
{
	ui.listWidget->clear();
	for (auto& q : service.getAllID())
	{
		ui.listWidget->addItem(QString::fromStdString(std::to_string(q.getId()) + " | " + q.getText() + " | " + q.getAnswer() + " | " + std::to_string(q.getScore())));
	}
}

