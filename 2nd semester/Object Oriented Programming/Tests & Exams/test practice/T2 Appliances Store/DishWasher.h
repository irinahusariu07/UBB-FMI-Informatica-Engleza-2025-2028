#pragma once
#include "Appliance.h"
class DishWasher : public Appliance
{
private: 
    double consumedEnergyForOneHour; 
public:
    DishWasher(const std::string& id, double consumedEnergyForOneHour) : Appliance{ id }, consumedEnergyForOneHour { consumedEnergyForOneHour } {}
    double consumeElectricity() override;
    std::string toString() override; 
};

