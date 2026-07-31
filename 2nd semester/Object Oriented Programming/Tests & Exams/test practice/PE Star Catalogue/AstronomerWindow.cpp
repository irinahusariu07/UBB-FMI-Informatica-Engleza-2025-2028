#include "AstronomerWindow.h"
#include"GraphicStars.h"

AstronomerWindow::AstronomerWindow(Service& s, const std::string& cc, const std::string&a, QWidget* parent)
	: QMainWindow(parent), service(s), current_constellation(cc), astronomer(a)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString("Astronomer: " + astronomer));
	ui.label->setText(QString::fromStdString(astronomer + " - " + current_constellation));
	service.registerObserver(this);
	model = new StarsListModel(service.getStars());
	listmodel = new StarsListModel(service.getStars());
	ui.tableView->setModel(model);
	ui.listView->setModel(listmodel);

	connect(ui.addBtn, &QPushButton::clicked, this, [=]
		{
			std::string name = ui.nameInput->text().toStdString();
			int diam = ui.diameterInput->text().toInt();
			int ra = ui.raInput->text().toInt();
			int dec = ui.decInput->text().toInt();
			try
			{
				service.addStar(name, current_constellation, ra, dec, diam);
			}
			catch (std::exception& e)
			{
				QMessageBox::critical(this, "Error:", e.what());
			}
		});

	connect(ui.checkBox, &QCheckBox::stateChanged, this, [=](int state)
		{
			std::vector<Star> display;
			if (state == Qt::Checked)
			{
				display = service.filterByConstellation(current_constellation);
			}
			else
			{
				display = service.getStars();
			}
			model->updateData(display);
		});

	connect(ui.progressiveName, &QLineEdit::textChanged, this, [=](const QString& text) {
		std::string txt = text.toStdString();
		std::vector<Star> result = service.getByName(txt);
		listmodel->updateData(result);
		});

	connect(ui.viewBtn, &QPushButton::clicked, this, [=]() {
		QModelIndex idx = ui.tableView->selectionModel()->currentIndex();
		if (!idx.isValid()) return;
		std::string name = idx.sibling(idx.row(), 0).data().toString().toStdString();
		std::string constell = idx.sibling(idx.row(), 1).data().toString().toStdString();

		std::vector<Star> stars = service.filterByConstellation(constell);
		auto* win = new GraphicStars(stars, name);
		win->show();
		});

	
}


AstronomerWindow::~AstronomerWindow()
{}

