#include "REDriverConnect.h"
#include <QtWidgets/QApplication>
#include"DriverMap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "drivers.txt", "reports.txt" };
    Service service{ repo };

    for (auto& d : repo.getDrivers())
    {
        auto* dWin = new REDriverConnect(service, d);
        dWin->show();
    }
    auto* map = new DriverMap(service);
    map->show();
    return app.exec();
}
