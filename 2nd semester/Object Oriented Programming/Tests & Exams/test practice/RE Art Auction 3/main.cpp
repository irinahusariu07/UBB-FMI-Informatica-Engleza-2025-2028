#include <qmessagebox.h>
#include <QtWidgets/QApplication>
#include "AdminWindow.h"
#include"CollectorWindow.h"
#include "Service.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "users.txt", "items.txt" };
    Service service{ repo };
    QMessageBox::information(nullptr, "info", "Items:" + QString::number(repo.getItems().size()) + "Users:" + QString::number(repo.getUsers().size()));

    for (auto& u : repo.getUsers())
    {
        if (u.getType() == "administrator")
        {
            auto* aWin = new AdminWindow(service, u);
            aWin->show();
        }
        else
        {
            auto* cWin = new CollectorWindow(service, u);
            cWin->show();
        }
    }

    return app.exec();
}
