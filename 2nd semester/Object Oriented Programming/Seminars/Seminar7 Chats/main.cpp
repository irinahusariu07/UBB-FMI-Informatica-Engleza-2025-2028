#include "Seminar7Chats.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Seminar7Chats window1;
    Seminar7Chats window2;
    window1.show();
    window2.show();
    return app.exec();
}
