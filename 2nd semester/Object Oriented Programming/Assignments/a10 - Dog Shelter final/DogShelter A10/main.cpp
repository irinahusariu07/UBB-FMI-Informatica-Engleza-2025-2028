#include "DogShelterGUIQTDesigner.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DogShelterGUIQTDesigner window;
    window.show();
    return app.exec();
}
