#include "REScreenWriter.h"

REScreenWriter::REScreenWriter(Service& ser, Writer w, const std::string& epfile, QWidget *parent)
    : QMainWindow(parent), service{ser}, writer{w}, episode_file {epfile}
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(writer.getName() + " " + writer.getExpertise())); 
    service.registerObs(this); 
    model = new IdeaList(service.getIdeasSorted(), writer); 
    ui.tableView->setModel(model);


    connect(ui.addBtn, &QPushButton::clicked, this, [=]()
        {
            std::string desc = ui.descInput->text().toStdString(); 
           int act = ui.actInput->text().toInt();

            try
            {
                //QMessageBox::information(this, "info", QString::fromStdString(writer.getName()));
                service.addIdea(desc, this->writer.getName(), act);
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "error: ", e.what());
            }
        });

    if (w.getExpertise() != "senior") ui.acceptBtn->hide();

    connect(ui.acceptBtn, &QPushButton::clicked, this, [=]()
        {
            std::string desc = ui.descInput->text().toStdString();
            int act = ui.actInput->text().toInt();
            try
            {
                service.acceptIdea(desc, act);
            }
            catch (std::exception& e)
            {
                QMessageBox::critical(this, "error: ", e.what());
            }

        });

    connect(ui.plotBtn, &QPushButton::clicked, this, [=]()
        {
            std::vector<Idea> result = service.getAcceptedSorted();
            std::ofstream file(episode_file);
            if (!file.is_open()) throw std::runtime_error("Cannot write episode");
            for (auto& i : result)
            {
                file << "Act: " << i.getAct() << " - " << i.getDesc() << " (" << i.getCreator() << ") \n";
            }
            file.close();

            QMessageBox::information(this, "Info: ", "Episode written");
        });

}

REScreenWriter::~REScreenWriter()
{}

