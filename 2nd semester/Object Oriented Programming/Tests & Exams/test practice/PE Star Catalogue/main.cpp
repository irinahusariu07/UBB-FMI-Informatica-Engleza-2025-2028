#include "AstronomerWindow.h"
#include "Service.h"
#include "Repo.h"
#include <QApplication>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<Astronomer> readAstronomers(const std::string& filename) {
    std::vector<Astronomer> astronomers;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, constellation;

        // Read until the pipe character
        if (std::getline(ss, name, '|') && std::getline(ss, constellation)) {
            astronomers.emplace_back(name, constellation);
        }
    }
    return astronomers;
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    Repo repo("stars.txt");
    Service service(repo);
    std::vector<Astronomer> astronomers = readAstronomers("astronomers.txt");

    for (const auto& astro : astronomers) {
        auto* win = new AstronomerWindow(service, astro.getConstellation(), astro.getName());
        win->show();
    }

    return a.exec();
}