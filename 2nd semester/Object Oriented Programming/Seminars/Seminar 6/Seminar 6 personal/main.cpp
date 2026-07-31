//#include "Seminar6personal.h"
#include"Repository.h"
#include"Seminar6GUI.h"
#include"StudentsModel.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repository repo{ "Students.txt" };
    StudentsModel* studentModel = new StudentsModel
    Seminar6GUI window;
    window.show();
    return app.exec();
}
