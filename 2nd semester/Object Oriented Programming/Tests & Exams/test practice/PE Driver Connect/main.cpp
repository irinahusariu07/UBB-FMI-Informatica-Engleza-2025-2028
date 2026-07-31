#include "PEDriverConnect.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try
    {
        Repo repo{ "drivers.txt", "reports.txt" };
        Service service{ repo };
        for (auto& d : service.getDrivers())
        {
            auto* tWin = new PEDriverConnect(service, d.getName(), d.getLat(), d.getLong(), d.getScore(), nullptr);
            tWin->show();
        }
        return app.exec();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, "ERROR: ", e.what());
        return -1;
    }
    
}
