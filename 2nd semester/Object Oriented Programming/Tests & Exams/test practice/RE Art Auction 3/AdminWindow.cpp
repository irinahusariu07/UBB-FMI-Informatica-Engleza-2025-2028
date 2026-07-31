#include "AdminWindow.h"

AdminWindow::AdminWindow(Service& serv, User& u, QWidget* parent)
	: QMainWindow(parent), service{ serv }, user{ u }
{
	ui.setupUi(this);
	service.registerObserver(this);
	this->setWindowTitle(QString::fromStdString(user.getType() + " " + user.getName()));
	//ui.label->setText(QString::fromStdString(user.getType() + " " + user.getName()));

	loadData();
	ui.comboBox->addItem(QString::fromStdString("ALL"));
	std::set<std::string> seen;
	for (auto& i : service.getItems()) {
		if (!seen.count(i.getCategory())) {
			seen.insert(i.getCategory());
			ui.comboBox->addItem(QString::fromStdString(i.getCategory()));
		}
	}

	connect(ui.addBtn, &QPushButton::clicked, this, [=]() {
		std::string name, category, pr;
		name = ui.nameInput->text().toStdString();
		category = ui.categoryInput->text().toStdString();
		pr = ui.priceInput->text().toStdString();
		try
		{
			service.addItem(name, category, std::stoi(pr));
		}
		catch (std::exception& e)
		{
			QMessageBox::critical(this, "Error: ", e.what());
		}
		});

	connect(ui.comboBox, &QComboBox::currentIndexChanged, this, [=](int index)
		{
			QString selected = ui.comboBox->itemText(index);
			ui.listWidget->clear();
			if (selected.toStdString() == "ALL") loadData();

			else
			{

				std::vector<Item> result = service.filterByCateg(selected.toStdString());
				for (auto& i : result)
				{
					ui.listWidget->addItem(QString::fromStdString(i.getName() + " | " + i.getCategory() + " | " + std::to_string(i.getCurrent())));
				}
			}
		});

	connect(ui.listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem* item)
		{
			QString line = item->text();
			QString name = line.split(" | ").at(0);
			ui.offerList->clear();

			for (auto& o : service.getOffers(name.toStdString()))
			{
				int id = std::get<0>(o);
				std::string date = std::get<1>(o);
				int val = std::get<2>(o);

				QString item_txt = QString::fromStdString(std::to_string(id) + " ~ " + date + " ~ " + std::to_string(val));
				ui.offerList->addItem(item_txt);
			}
		});

}



AdminWindow::~AdminWindow()
{
}

void AdminWindow::loadData()
{
	ui.listWidget->clear();
	for (auto& i : service.getItems())
	{
		ui.listWidget->addItem(QString::fromStdString(i.getName() + " | " + i.getCategory() + " | " + std::to_string(i.getCurrent())));
	}
}

