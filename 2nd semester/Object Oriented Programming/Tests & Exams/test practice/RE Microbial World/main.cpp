#include "REMicrobialWorld.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "biologist.txt", "bacteria.txt" };
    Service service{ repo };
    //QMessageBox::information(nullptr, "info", QString::fromStdString("bacteria " + std::to_string(repo.getBacteria().size())));

    for (auto& b : repo.getBiologists())
    {
        auto* bWin = new REMicrobialWorld(service, b);
        bWin->show(); 
    }
    return app.exec();
}
