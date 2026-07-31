#include "Refrigerator.h"

double Refrigerator::consumeElectricity()
{
    int quantity = 0; 
    if (privateUsageClass == "a") quantity = 90; 
    if (privateUsageClass == "a++") quantity = 60;
    if (hasFreezer == true) quantity += 20; 
    return quantity; 
}

std::string Refrigerator::toString()
{
    if (hasFreezer == false) return "id: " + id + " usage class: " + privateUsageClass + " consume: " + std::to_string(consumeElectricity()) + " has freezer: no" + "\n";
    else return "id: " + id + " usage class: " + privateUsageClass + " consume: " + std::to_string(consumeElectricity()) + " has freezer: yes" + "\n";
}


