#include "CollectorWindow.h"

CollectorWindow::CollectorWindow(Service& ser, User usr, QWidget* parent)
	: QMainWindow(parent), service{ ser }, user{ usr }
{
	ui.setupUi(this);
	service.registerObserver(this);
	this->setWindowTitle(QString::fromStdString(user.getType() + " " + user.getName()));
	//ui.label->setText(QString::fromStdString(user.getType() + " " + user.getName()));


	loadDataMain();
	ui.comboBox->addItem(QString::fromStdString("ALL"));
	std::set<std::string> seen;
	for (auto& i : service.getItems()) {
		if (!seen.count(i.getCategory())) {
			seen.insert(i.getCategory());
			ui.comboBox->addItem(QString::fromStdString(i.getCategory()));
		}
	}


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

	connect(ui.comboBox, &QComboBox::currentIndexChanged, this, [=](int index)
		{
			QString selected = ui.comboBox->itemText(index);
			ui.listWidget->clear();
			if (selected.toStdString() == "ALL") loadDataMain();
			else
			{
				std::vector<Item> result = service.filterByCateg(selected.toStdString());
				for (auto& i : result)
				{
					ui.listWidget->addItem(QString::fromStdString(i.getName() + " | " + i.getCategory() + " | " + std::to_string(i.getCurrent())));
				}
			}

		});

	connect(ui.bidBtn, &QPushButton::clicked, this, [=]() {
		std::string val, date, name;
		val = ui.priceInput->text().toStdString();
		date = ui.dateInput->text().toStdString();
		name = ui.nameInput->text().toStdString();

		try
		{
			service.addOffer(name, user.getID(), date, std::stoi(val));
		}
		catch (std::exception& e)
		{
			QMessageBox::critical(this, "Error: ", e.what());
		}

		});


}

CollectorWindow::~CollectorWindow()
{
}

void CollectorWindow::loadDataMain()
{
	ui.listWidget->clear();
	std::vector<Item>result = service.getItems();
	for (auto& i : result)
	{
		ui.listWidget->addItem(QString::fromStdString(i.getName() + " | " + i.getCategory() + " | " + std::to_string(i.getCurrent())));
	}
}

