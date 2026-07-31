#include "Service.h"

void Service::readFromFile()
{
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("FILE CORRUPTED");
    std::string line;
    while (getline(file, line))
    {
        if (line.empty()) continue; 
        std::stringstream ss(line); 
        std::string man, mod, syear, color;
        int year; 
        std::getline(ss, man, '|');
        std::getline(ss, mod, '|');
        std::getline(ss, syear, '|');
        year = stoi(syear);
        std::getline(ss, color, '|');
        Car c{ man, mod, year, color };
        allCars.push_back(c);
    }
    file.close();
}

std::vector<Car> Service::getAll()
{
    std::sort(allCars.begin(), allCars.end(), [](Car& c1, Car& c2) {
        return c1.getManufacturer() < c2.getManufacturer();
        });
    return allCars;
}

std::vector<Car> Service::getCarsFromManufacturer(const std::string& manufacturer)
{
    std::vector<Car> all = getAll();
    std::vector<Car> by_manuf; 
    for (auto& c : all)
    {
        if (c.getManufacturer() == manufacturer) by_manuf.push_back(c);
    }
    return by_manuf; 
}
