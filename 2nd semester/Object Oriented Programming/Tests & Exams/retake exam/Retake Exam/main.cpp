#include "RetakeExam.h"
#include"Repo.h"
#include"ChefWindow.h"
#include"GraphicalRecipes.h"
#include <QtWidgets/QApplication>
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "chefs.txt", "recipes.txt" };
    Service service{ repo };

    /*std::vector<std::string> ing{ "meat", "bdj" };
    Recipe r{ "mici", "romanian", 20, ing };
    repo.addRecipe(r);
    QMessageBox::information(nullptr, "info", QString::fromStdString("chefs: " + std::to_string(repo.getChefs().size()) + "recipes: " + std::to_string(repo.getRecipes().size())));
    */

    auto* gWin = new GraphicalRecipes(service);
    gWin->show();
    for (auto& c : service.getChefs())
    {
        auto* cWin = new ChefWindow(service, c);
        cWin->show();
    }
    return app.exec();
}
