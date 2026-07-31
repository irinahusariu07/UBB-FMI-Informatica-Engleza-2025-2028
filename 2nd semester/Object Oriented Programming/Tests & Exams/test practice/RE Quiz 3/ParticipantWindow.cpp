#include "ParticipantWindow.h"

ParticipantWindow::ParticipantWindow(Service& s, Participant pa, QWidget* parent)
	: QMainWindow(parent), service{ s }, particip{ pa }
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(particip.getName()));
	service.registerObs(this); 
	loadData(); 
	ui.label->setText("0");

	connect(ui.answBtn, &QPushButton::clicked, this, [=]()
		{
			std::string ans = ui.ansInput->text().toStdString();
			int id = ui.idInput->text().toInt(); 
			try
			{
				answered.insert(id);
				if (service.correctAns(id, ans))
				{
					service.updateScore(particip.getName(), service.getScoreById(id));
					ui.label->setText(QString::number(service.getScoreById(id)));
				}
				ui.listWidget->clear();
				for (auto& q : service.getAllScore())
				{
					QString text = QString::fromStdString(std::to_string(q.getId()) + " | " + q.getText() + " | " + std::to_string(q.getScore()));
					QListWidgetItem* item = new QListWidgetItem(text);
					if (answered.count(q.getId())) item->setBackground(QBrush(QColor("green")));
					ui.listWidget->addItem(item);
				}

			}
			catch (std::exception& e)
			{
				QMessageBox::critical(this, "Error: ", e.what());
			}
		});
}

ParticipantWindow::~ParticipantWindow()
{}

void ParticipantWindow::loadData()
{
	ui.listWidget->clear();
	for (auto& q : service.getAllScore())
	{
		ui.listWidget->addItem(QString::fromStdString(std::to_string(q.getId()) + " | " + q.getText() + " | " + std::to_string(q.getScore())));
	}
}

