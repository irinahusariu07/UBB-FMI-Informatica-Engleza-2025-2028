#include "DishWasher.h"

double DishWasher::consumeElectricity()
{
    return consumedEnergyForOneHour * 20; 
}

std::string DishWasher::toString()
{
    return "id: " + id + " consumed energy for 1 hour: " + std::to_string(consumedEnergyForOneHour) + "\n";
}

