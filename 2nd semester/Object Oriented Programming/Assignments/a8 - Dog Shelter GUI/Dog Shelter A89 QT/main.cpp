#include "DogShelterA89QT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DogShelterA89QT window;
    window.show();
    return app.exec();
}
