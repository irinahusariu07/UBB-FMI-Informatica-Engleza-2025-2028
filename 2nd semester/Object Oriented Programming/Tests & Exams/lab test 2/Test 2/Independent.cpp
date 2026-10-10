#include "Independent.h"

bool Independent::eligible()
{
    return (mandates() > 1);
}

int Independent::mandates()
{
    return votes/100;
}

std::string Independent::toString()
{
    return " Name: " + name + " County: " + getCounty() + " Mandates: " + std::to_string(mandates()) + "\n";
}



