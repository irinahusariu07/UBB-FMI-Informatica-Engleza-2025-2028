#include "T3Cars.h"
#include <QtWidgets/QApplication>
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Service* s = nullptr; 
    try {
        s = new Service("cars.txt");
        s->readFromFile();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error: ", e.what());
    }
    T3Cars window(s);
    window.show();
    return app.exec();
}
