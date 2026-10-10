#include "Party.h"
 

bool Party::eligible()
{
    if (votes * 100 / 250 > 5 / 100) return true; //passes 5% 
    return false; 
}

int Party::mandates()
{
    return (votes * 100 / 250)/100 * (329 * votes / 250);
}

std::string Party::toString()
{
    if (eligible() == true) return "County: " + getCounty() + " Name: " + name + " Votes: " + std::to_string(votes) + " Eligible: yes " + " Mandates: " + std::to_string(mandates()) + "\n";
    else return "County: " + getCounty() + " Name: " + name + " Votes: " + std::to_string(votes) + " Eligible: no " + " Mandates: " + std::to_string(mandates()) + "\n";
}


