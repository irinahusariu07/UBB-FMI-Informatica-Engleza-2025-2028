#include "ProgrammerWindow.h"
#include"TesterWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "users.txt", "issues.txt" };
    Service service{ repo };
	std::ifstream file("users.txt");
	if (!file.is_open()) throw std::runtime_error("User file corrupted!");
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string name, type;
		std::getline(ss, name, '|');
		std::getline(ss, type, '|');
		if (type == "programmer")
		{
			auto* pWin = new ProgrammerWindow(service, name);
			pWin->show();
		}
		else if (type == "tester")
		{
			auto* tWin = new TesterWindow(service, name);
			tWin->show();
		}
	}
	file.close();

    return app.exec();
}
