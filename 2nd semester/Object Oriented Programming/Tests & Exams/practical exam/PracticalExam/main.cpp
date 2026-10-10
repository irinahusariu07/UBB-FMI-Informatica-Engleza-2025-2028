#include "AgentWindow.h"
#include "LogisticsDashboard.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "agent.txt", "parcel.txt" };
    Service service{ repo };
    LogisticsDashboard window(service);
    window.show();
    try
    {
        for (auto& a : service.getAgents())
        {
            auto* aWin = new AgentWindow(service, a.getName(), a.getRad(), a.getCircleX(), a.getCircleY());
            aWin->show();
        }
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error:", e.what());
    }
    return app.exec();
}
