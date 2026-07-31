#include "Service.h"

std::vector<Bacteria>& Service::getBacteria()
{   
    std::vector<Bacteria>& result = repo.getBacteria();
    std::sort(result.begin(), result.end(), [&](const Bacteria& b1, const Bacteria& b2)
        {
            return b1.getName() < b2.getName();
        });
    return result;
}

std::vector<Bacteria> Service::getBacteriaForBiologist(std::vector<std::string> list)
{
    std::vector<Bacteria> result; 
    for (auto& i : list)
    {
        for (auto& j : getBacteria())
        {
            if (j.getSpecies() == i) result.push_back(j); 
        }
    }
    std::sort(result.begin(), result.end(), [&](const Bacteria& b1, const Bacteria& b2)
        {
            return b1.getName() < b2.getName();
        });
    return result; 
}

std::vector<Bacteria> Service::filterSpecies(const std::string& spec)
{
    std::vector<Bacteria> result;
    for (auto& j : getBacteria())
    {
        if (j.getSpecies() == spec) result.push_back(j);
    }
    std::sort(result.begin(), result.end(), [&](Bacteria b1, Bacteria b2)
        {
            return b1.getName() < b2.getName();
        });
    return result;
}

void Service::addBacteria(const std::string& name, const std::string& species, int size, const std::string& dis)
{
    if (name.empty() || species.empty() || size < 0) throw std::runtime_error("Invalid data"); 

    for (auto& b : getBacteria())
    {
        if (b.getName() == name && b.getSpecies() == species) throw std::runtime_error("Already Exists"); 
    }
    std::stringstream ss(dis); 
    std::string d;
    std::vector<std::string> vectd; 
    while (std::getline(ss, d, ';'))
    {
        if (d.empty()) continue; 
        vectd.push_back(d); 
    }
    Bacteria b{ name, species, size, vectd };
    repo.addBacteria(b);
    notifyObs();
}

std::vector<std::string> Service::getDiseases(const std::string& name, const std::string& spec)
{
    for (auto& b : getBacteria())
    {
        if (b.getName() == name && b.getSpecies() == spec) return b.getDiseases();
    }
    throw std::runtime_error("Doesnt exist");
}


