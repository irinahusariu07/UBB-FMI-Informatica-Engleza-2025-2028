#include "ChefWindow.h"

ChefWindow::ChefWindow(Service& s, Chef c, QWidget *parent)
	: QMainWindow(parent), service{s}, chef{c}
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(c.getName()));
	service.registerObs(this); 

	loadData(); 

	connect(ui.checkBox, &QCheckBox::stateChanged, this, [=](int state)
		{
			if (state == Qt::Checked)
			{
				std::vector<Recipe> result = service.getAllCuisine(c.getCuisine());
				ui.listWidget->clear();

				for (auto& r : result)
				{
					ui.listWidget->addItem(QString::fromStdString(r.getName() + " | " + r.getCuisine() + " | " + std::to_string(r.getTime()) + " | " + r.formatIng()));
				}

			}

			else loadData();
		});

	connect(ui.addBtn, &QPushButton::clicked, this, [=]()
		{
			std::string name = ui.nameInput->text().toStdString();
			int time = ui.timeInput->text().toInt();
			std::string ing_list = ui.ingredientsInput->text().toStdString();

			try
			{
				service.addRecipe(name, c.getCuisine(), time, ing_list);
			}
			catch (std::exception& e)
			{
				QMessageBox::critical(this, "Error: ", e.what());
			}
		});

	connect(ui.searchBtn, &QPushButton::clicked, this, [=]()
		{
			std::string ing_list = ui.searchInput->text().toStdString();
			std::vector<Recipe> result = service.filterIngredients(ing_list);

			ui.listWidget->clear();
			for (auto& r : result)
			{
				ui.listWidget->addItem(QString::fromStdString(r.getName() + " | " + r.getCuisine() + " | " + std::to_string(r.getTime()) + " | " + r.formatIng()));
			}

			if (result.empty())
			{
				QMessageBox::information(this, "Info: ", QString::fromStdString("No recipe contains all searched ingredients \n Showing all recipes."));
				loadData();
			}
		});

}

ChefWindow::~ChefWindow()
{}

void ChefWindow::loadData()
{
	ui.listWidget->clear(); 

	for (auto& r : service.getAllSorted())
	{
		ui.listWidget->addItem(QString::fromStdString(r.getName() + " | " + r.getCuisine() + " | " + std::to_string(r.getTime()) + " | " + r.formatIng()));
	}
}

