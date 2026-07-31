#include "Service.h"

std::vector<Appliance*> Service::getAllWithCEnergyLessThan(double maxE)
{
    std::vector<Appliance*> corresponding; 
    for (auto a : appliances)
    {
        if (a->consumeElectricity() < maxE) corresponding.push_back(a);
    }
    return corresponding; 
}

void Service::writeToFile(const std::string& filename, double maxE)
{
    std::ofstream file(filename);
    std::vector<Appliance*> corresponding = getAllWithCEnergyLessThan(maxE);
    std::sort(corresponding.begin(), corresponding.end(), [](Appliance* a, Appliance* b)
        {
            return a->getID() < b->getID();
        });

    for (auto a : corresponding)
    {
        file << a->toString() << "\n";
    }
    file.close();
}
