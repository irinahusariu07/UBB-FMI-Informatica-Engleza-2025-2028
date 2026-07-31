#include <QtWidgets/QApplication>
#include "Repository.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Repository repo{"Students.txt"};

	return a.exec();
}
