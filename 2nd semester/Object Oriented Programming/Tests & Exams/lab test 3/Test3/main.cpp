#include "Test3.h"
#include <QtWidgets/QApplication>
#include"Service.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Service* s = nullptr;
    try {
        s = new Service("airport.txt");
        s->readFromFile();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error: ", e.what());
        return -1;
    }
    Test3 window(s);
    window.show();
    return app.exec();
}
