#include "REScreenWriter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "writers.txt", "ideas.txt" };
        Service service{ repo };
        QMessageBox::information(nullptr, "info", QString::fromStdString("writers: " + std::to_string(repo.getWriters().size()) + "ideas: " + std::to_string(repo.getIdeas().size())));

        for (auto& w : repo.getWriters())
        {
            auto* wWin = new REScreenWriter(service, w, "episode.txt");
            wWin->show(); 
        }
    return app.exec();
}
