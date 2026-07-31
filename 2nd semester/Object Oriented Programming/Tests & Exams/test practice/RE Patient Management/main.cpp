#include "REPatientManagement.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo("doctors.txt", "patients.txt");
    Service service{ repo };
    try
    {
        for (auto& d : service.getDoctors())
        {
            auto* dWin = new REPatientManagement(service, d.getName());
            dWin->show();
        }
    }
    catch (std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error: ", e.what());
    }
    return app.exec();
}
