#pragma once
#include "County.h"
class Independent :
    public County
{
    std::string name; 
    int votes; 

public:
    Independent(const std::string& county, const std::string& name, int votes) : County(county), name{ name }, votes{ votes } {}
    bool eligible() override; 
    int mandates() override; 
    std::string toString() override; 
};

