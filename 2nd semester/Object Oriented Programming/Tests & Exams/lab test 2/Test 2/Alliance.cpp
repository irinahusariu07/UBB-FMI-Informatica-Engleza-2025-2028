#include "Alliance.h"

bool Alliance::eligible()
{
    if (number == 2 && votes * 100 / 250 >= 8 / 100) return true;
    else if (number == 3 && votes * 100 / 250 >= 9 / 100) return true;
    else if (number > 3 && votes * 100 / 250 >= 10 / 100) return true;
    return false;
}

int Alliance::mandates()
{
    return 329 * votes / 250; 
}

std::string Alliance::toString()
{
    return "Name: " + name + "County: " + getCounty() + "Parties: " + std::to_string(number) +  "Votes: " + std::to_string(votes) + "Mandates: " + std::to_string(mandates()) + "\n";
}



