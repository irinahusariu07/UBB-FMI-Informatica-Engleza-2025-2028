#include "T3Bills.h"
#include <QtWidgets/QApplication>
#include "Service.h"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MAIN
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Service* s = nullptr;
    try {
        s = new Service("bills.txt");
        s->readFromFile();
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error: ", e.what());
        return -1; 
    }
    T3Bills window(s);
    window.show();
    return app.exec();
}
